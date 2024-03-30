#include "RootFrame.h"
#include <wx\wx.h>

RootFrame::RootFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel* panel = new wxPanel(this);

    wxButton* boton1 = new wxButton(panel, wxID_ANY, wxString("button1"), wxPoint(400, 400));
    wxButton* boton2 = new wxButton(panel, wxID_ANY, wxString("button2"), wxPoint(400, 200));
    panel->Bind(wxEVT_BUTTON, &RootFrame::on_button_click, this);

    CreateStatusBar();
}

void RootFrame::on_button_click(wxCommandEvent& evt)
{
    wxLogMessage("Wazaaaa");
}

