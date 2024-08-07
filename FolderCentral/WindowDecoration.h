#ifndef WINDOWDECORATION_H
#define WINDOWDECORATION_H

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <string>
#include <filesystem>
#include <sstream>
#include <vector>
#include "Functionality.h"
#include "RootFrame.h"

namespace fcw 
{
    void kill_all_children(wxPanel* panel);
    void decorate_left_panel(wxPanel* left_panel, wxPanel* right_panel);
    void add_folder_window(wxCommandEvent& event, wxWindow* root, wxPanel* left_panel, wxPanel* right_panel);
    void save_folder(wxCommandEvent& event, wxStatusBar* status, wxTextCtrl* entry, wxPanel* left_panel, wxPanel* right_panel);
    void search_folder_path(wxCommandEvent& event, wxFrame* frame, wxTextCtrl* entry);
    void decorate_right_panel(wxCommandEvent& event, wxPanel* right_panel, wxString folder_path);
    void subroutine_button(wxCommandEvent& event, std::string subroutine_path);
    void create_subroutine_window(wxCommandEvent& event, wxPanel* right_panel, std::string folder_path);
}

#endif
