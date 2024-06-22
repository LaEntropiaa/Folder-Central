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
    void add_folder(wxCommandEvent& event, wxWindow* root);
    

}

#endif
