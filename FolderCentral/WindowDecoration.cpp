#include "WindowDecoration.h"

void fcw::kill_all_children(wxPanel* panel)
{
    wxWindowList children = panel->GetChildren();
    for (wxWindowList::iterator it = children.begin(); it != children.end(); ++it)
    {
        wxWindow* child = *it;
        panel->RemoveChild(child);
        child->Destroy();
    }
}


void fcw::decorate_left_panel(wxPanel* left_panel, wxPanel* right_panel)
{
    left_panel->SetBackgroundColour(wxColor(38, 113, 15));
    wxSizer* panel_sizer = new wxBoxSizer(wxVERTICAL);
    std::string file_path = "../configuration/saved_subroutines_directories.txt";

    //if not existent the configuration directory then create one
    if (!(std::filesystem::exists(std::filesystem::path("../configuration")) && std::filesystem::is_directory(std::filesystem::path("../configuration"))))
    {
        std::filesystem::create_directory(std::filesystem::path("../configuration"));
        std::ofstream file;
        file.open(file_path);
        file.close();
    }//if the configuration file required doesn't exits then create one
    else if (!(std::filesystem::exists(std::filesystem::path(file_path)) && std::filesystem::is_regular_file(file_path)))
    {
        std::ofstream file;
        file.open(file_path);
        file.close();
    }
    
    std::string line;
    std::ifstream data;
    std::vector<std::string> directories;
    data.open(file_path);
    while (std::getline(data, line))
    {
        directories.push_back(line);
    }
    //Get the right panel without passing the right panel directly
    for (std::string directory : directories)
    {
        if (directory.empty())
        {
            continue;
        }
        std::filesystem::path path(directory);
        wxString wxdirectory = wxString(directory);
        wxButton* button = new wxButton(left_panel, wxID_ANY, path.filename().string(), wxDefaultPosition, wxSize(250, 30), 0L, wxDefaultValidator, wxdirectory);
        panel_sizer->Add(button, 0, wxEXPAND | wxALL, 0);
        button->Bind(wxEVT_BUTTON, [right_panel, wxdirectory](wxCommandEvent& event)
            {
                fcw::decorate_right_panel(event, right_panel, wxdirectory);
            });
    }

    wxWindow* root = left_panel->GetParent();
    wxButton* new_folder_button = new wxButton(left_panel, wxID_ANY, "+", wxDefaultPosition, wxSize(250, 40));
    new_folder_button->Bind(wxEVT_BUTTON, [root, left_panel, right_panel](wxCommandEvent& event)
        {
            fcw::add_folder_window(event, root, left_panel, right_panel);
        });
    panel_sizer->Add(new_folder_button, 0, wxEXPAND | wxALL, 0);

    left_panel->SetSizerAndFit(panel_sizer);

}


void fcw::add_folder_window(wxCommandEvent& event, wxWindow* root, wxPanel* left_panel, wxPanel* right_panel)
{
    wxWindowList children = root->GetChildren();
    for (wxWindowList::iterator it = children.begin(); it != children.end(); ++it)
    {
        wxFrame* frame = dynamic_cast<wxFrame*>(*it);
        if (frame)
        {
            frame->Destroy();
        }
    }

    wxFrame* dialog_frame = new wxFrame(root, wxID_ANY, "Add a new folder");
    dialog_frame->SetMinSize(wxSize(450, 160));
    dialog_frame->SetMaxSize(wxSize(450, 160));

    wxStatusBar* status = new wxStatusBar(dialog_frame, wxID_ANY);
    dialog_frame->SetStatusBar(status);

    wxPanel* panel = new wxPanel(dialog_frame, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel->SetBackgroundColour(wxColor(200, 100, 200));

    wxTextCtrl* entry = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 15), wxSize(390, 20));
    entry->SetMaxLength(100);

    wxButton* add_button = new wxButton(panel, wxID_ANY, "Add", wxPoint(20, 55));
    add_button->Bind(wxEVT_BUTTON, [status, entry, left_panel, right_panel](wxCommandEvent& event)
        {
            fcw::save_folder(event, status, entry, left_panel, right_panel);
        });

    wxButton* search_button = new wxButton(panel, wxID_ANY, "Search", wxPoint(335, 55));
    search_button->Bind(wxEVT_BUTTON, [dialog_frame, entry](wxCommandEvent& event)
        {
            fcw::search_folder_path(event, dialog_frame, entry);
        });

    dialog_frame->Center();
    dialog_frame->Show();
}

void fcw::save_folder(wxCommandEvent& event, wxStatusBar* status, wxTextCtrl* entry, wxPanel* left_panel, wxPanel* right_panel)
{
    std::string path = entry->GetValue().ToStdString();
    std::filesystem::path new_folder(fcf::raw_path(path));
    if (!(std::filesystem::exists(path) && std::filesystem::is_directory(path)))
    {
        status->SetStatusText(wxString("Invalid path!"));
        entry->Clear();
        return;
    }

    std::ofstream file;
    file.open("../configuration/saved_subroutines_directories.txt", std::ios_base::app);
    file << path << "\n";
    file.close();

    left_panel->Freeze();
    left_panel->DestroyChildren();
    fcw::decorate_left_panel(left_panel, right_panel);
    entry->Clear();
    left_panel->Layout();
    left_panel->Thaw();
    left_panel->Refresh();
    left_panel->Update();
}


void fcw::search_folder_path(wxCommandEvent& event, wxFrame* frame, wxTextCtrl* entry)
{
    wxDirDialog* folder_dialog = new wxDirDialog(frame);
    
    
    if (folder_dialog->ShowModal() == wxID_OK)
    {
        wxString path = folder_dialog->GetPath();
        entry->SetValue(path);
    }
    folder_dialog->Destroy();
}


void fcw::decorate_right_panel(wxCommandEvent& event, wxPanel* right_panel, wxString folder_path)
{
    if(!right_panel) 
    {
        wxLogError("Right panel is null!");
        return;
    }
    right_panel->Freeze();  
    right_panel->DestroyChildren();
    right_panel->SetBackgroundColour(wxColour(100, 220, 100));
    
    wxWrapSizer* sizer = new wxWrapSizer(wxHORIZONTAL);
    right_panel->SetSizer(sizer);

    std::vector<std::string> subroutine_paths = fcf::get_directory_subroutines(folder_path.ToStdString());
    for (std::string path : subroutine_paths)
    {
        std::string name = std::filesystem::path(path).filename().string();
        name = name.substr(0, name.length() - 4);
        wxButton* button = new wxButton(right_panel, wxID_ANY, name, wxDefaultPosition, wxSize(90, 90), 0L, wxDefaultValidator);
        button->Bind(wxEVT_BUTTON, [path](wxCommandEvent& event)
            {
                fcw::subroutine_button(event, path);
            });
        sizer->Add(button, 0, wxALL, 5);
    }

    std::string directory = folder_path.ToStdString();
    wxWindow* root = right_panel->GetParent();
    wxButton* add_subroutine_button = new wxButton(right_panel, wxID_ANY, "+", wxDefaultPosition, wxSize(90, 90));
    add_subroutine_button->Bind(wxEVT_BUTTON, [right_panel, directory](wxCommandEvent& event)
        {
            fcw::create_subroutine_window(event, right_panel, directory);
        });
    sizer->Add(add_subroutine_button, 0, wxALL, 5);

    right_panel->Layout();
    right_panel->Thaw();
    right_panel->Refresh();
    right_panel->Update();
}


void fcw::subroutine_button(wxCommandEvent& event, std::string subroutine_path)
{
    wxMessageDialog* confirmation_dialog = new wxMessageDialog(NULL, wxString("Are you sure you want to execute this subroutine?"), "Confirm", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
    if (confirmation_dialog->ShowModal() == wxID_YES)
    {
        fcf::execute_subroutine(subroutine_path);
        wxLogMessage("Subroutine executed!");
    }
}


void fcw::create_subroutine_window(wxCommandEvent& event, wxPanel* right_panel, std::string folder_path)
{
    wxWindowList children = right_panel->GetChildren();
    for (wxWindowList::iterator it = children.begin(); it != children.end(); ++it)
    {
        wxFrame* frame = dynamic_cast<wxFrame*>(*it);
        if (frame)
        {
            frame->Destroy();
        }
    }

    wxFrame* dialog_frame = new wxFrame(right_panel, wxID_ANY, "Create a new subroutine");
    dialog_frame->SetMinSize(wxSize(400, 600));
    dialog_frame->SetMaxSize(wxSize(400, 600));

    //dialog_frame->CentreOnParent();
    dialog_frame->SetPosition(wxGetMousePosition());
    dialog_frame->Show();
}