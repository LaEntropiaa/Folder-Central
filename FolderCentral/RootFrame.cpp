#include "RootFrame.h"
#include <wx\wx.h>
#include <string>

RootFrame::RootFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    //RootFrame config
    SetMinSize(wxSize(400, 300));

    wxPanel* panel_left = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(250, 100));
    panel_left->SetBackgroundColour(wxColor(38, 113, 15));



    wxPanel* panel_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    panel_right->SetBackgroundColour(wxColor(254, 111, 71));

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel_left, 0, wxEXPAND | wxALL, 5);
    sizer->Add(panel_right, 1, wxEXPAND | wxALL, 5);

    this->SetSizerAndFit(sizer);

}

