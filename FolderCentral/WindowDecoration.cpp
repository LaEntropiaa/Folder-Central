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
        std::filesystem::path path(directory);
        wxButton* button = new wxButton(left_panel, wxID_ANY, path.filename().string(), wxDefaultPosition, wxSize(250, 30));
        panel_sizer->Add(button, 0, wxEXPAND | wxALL, 0);
    }

    wxWindow* root = left_panel->GetParent();
    wxButton* new_folder_button = new wxButton(left_panel, wxID_ANY, "+", wxDefaultPosition, wxSize(250, 40));
    new_folder_button->Bind(wxEVT_BUTTON, [root](wxCommandEvent& event)
        {
            fcw::add_folder(event, root);
        });
    panel_sizer->Add(new_folder_button, 0, wxEXPAND | wxALL, 0);

    left_panel->SetSizerAndFit(panel_sizer);

}


void fcw::add_folder(wxCommandEvent& event, wxWindow* root)
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
    dialog_frame->SetMinSize(wxSize(300, 100));
    dialog_frame->SetMaxSize(wxSize(300, 100));

    wxPanel* panel = new wxPanel(dialog_frame, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    dialog_frame->Center();
    dialog_frame->Show();
}


