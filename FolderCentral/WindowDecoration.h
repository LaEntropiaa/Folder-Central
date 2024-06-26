#ifndef WINDOWDECORATION_H
#define WINDOWDECORATION_H

#include <wx/wx.h>
#include <string>
#include <filesystem>
#include <sstream>
#include <vector>
#include "Functionality.h"

namespace fcw 
{
    void kill_all_children(wxPanel* panel);
    void decorate_left_panel(wxPanel* left_panel);
    void add_folder_window(wxCommandEvent& event, wxWindow* root, wxPanel* left_panel);
    void add_folder_button(wxCommandEvent& event, wxStatusBar* status, wxTextCtrl* entry, wxPanel* left_panel);
    void search_folder_path(wxCommandEvent& event, wxFrame* frame, wxTextCtrl* entry);
}

#endif
