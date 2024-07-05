#include "RootFrame.h"
#include <wx\wx.h>
#include <string>

RootFrame::RootFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    //RootFrame config
    SetMinSize(wxSize(800, 600));

    wxPanel* right_panel = new wxPanel(this, 400, wxDefaultPosition, wxSize(550, 600), 2621440L, wxString("right_panel"));
    right_panel->SetBackgroundColour(wxColor(254, 111, 71));

    wxPanel* left_panel = new wxPanel(this, 41, wxDefaultPosition, wxSize(250, 600), 2621440L, wxString("left_panel"));
    left_panel->SetBackgroundColour(wxColor(38, 113, 15));
    fcw::decorate_left_panel(left_panel, right_panel);

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(left_panel, 0, wxEXPAND | wxALL, 5);
    sizer->Add(right_panel, 1, wxEXPAND | wxALL, 5);

    this->SetSizerAndFit(sizer);
}

