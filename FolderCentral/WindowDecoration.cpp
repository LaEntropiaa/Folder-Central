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


void fcw::decorate_left_panel(wxPanel* left_panel)
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

    for (std::string directory : directories)
    {
        if (directory.empty())
        {
            continue;
        }
        std::filesystem::path path(directory);
        wxButton* button = new wxButton(left_panel, wxID_ANY, path.filename().string(), wxDefaultPosition, wxSize(250, 30));
        panel_sizer->Add(button, 0, wxEXPAND | wxALL, 0);
    }

    wxWindow* root = left_panel->GetParent();
    wxButton* new_folder_button = new wxButton(left_panel, wxID_ANY, "+", wxDefaultPosition, wxSize(250, 40));
    new_folder_button->Bind(wxEVT_BUTTON, [root, left_panel](wxCommandEvent& event)
        {
            fcw::add_folder_window(event, root, left_panel);
        });
    panel_sizer->Add(new_folder_button, 0, wxEXPAND | wxALL, 0);

    left_panel->SetSizerAndFit(panel_sizer);

}


void fcw::add_folder_window(wxCommandEvent& event, wxWindow* root, wxPanel* left_panel)
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
    add_button->Bind(wxEVT_BUTTON, [status, entry, left_panel](wxCommandEvent& event)
        {
            fcw::add_folder_button(event, status, entry, left_panel);
        });

    wxButton* search_button = new wxButton(panel, wxID_ANY, "Search", wxPoint(335, 55));
    search_button->Bind(wxEVT_BUTTON, [dialog_frame, entry](wxCommandEvent& event)
        {
            fcw::search_folder_path(event, dialog_frame, entry);
        });

    dialog_frame->Center();
    dialog_frame->Show();
}

void fcw::add_folder_button(wxCommandEvent& event, wxStatusBar* status, wxTextCtrl* entry, wxPanel* left_panel)
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

    fcw::kill_all_children(left_panel);
    fcw::decorate_left_panel(left_panel);
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