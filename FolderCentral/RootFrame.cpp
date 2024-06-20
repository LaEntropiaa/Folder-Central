#include "RootFrame.h"
#include <wx\wx.h>
#include <string>

RootFrame::RootFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    //RootFrame config
    SetMinSize(wxSize(800, 600));

    wxPanel* left_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(250, 600));
    left_panel->SetBackgroundColour(wxColor(38, 113, 15));
    fcw::decorate_left_panel(left_panel);

    wxPanel* right_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(550, 600));
    right_panel->SetBackgroundColour(wxColor(254, 111, 71));

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(left_panel, 0, wxEXPAND | wxALL, 5);
    sizer->Add(right_panel, 1, wxEXPAND | wxALL, 5);

    this->SetSizerAndFit(sizer);

}

