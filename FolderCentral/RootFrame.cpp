#include "RootFrame.h"
#include <wx\wx.h>
#include <string>

RootFrame::RootFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel* panel = new wxPanel(this);
    
    panel->Bind(wxEVT_LEFT_DOWN, &RootFrame::on_mouse_event, this);

    CreateStatusBar();
}

void RootFrame::on_mouse_event(wxMouseEvent& evt)
{
    this->num++;
    std::string str = std::to_string(this->num);
    const char* chr = str.c_str();
    wxLogStatus(chr);
}