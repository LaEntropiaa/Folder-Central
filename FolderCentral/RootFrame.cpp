#include "RootFrame.h"
#include <wx\wx.h>

RootFrame::RootFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel* panel = new wxPanel(this);
    
    wxButton* boton1 = new wxButton(panel, wxID_ANY, wxString("button1"), wxPoint(400, 400));
    wxButton* boton2 = new wxButton(panel, wxID_ANY, wxString("button2"), wxPoint(400, 200));
    
    panel->Bind(wxEVT_BUTTON, &RootFrame::on_any_button_click, this);
    boton1->Bind(wxEVT_BUTTON, &RootFrame::on_button1_click, this);
    boton2->Bind(wxEVT_BUTTON, &RootFrame::on_button2_click, this);

    CreateStatusBar();
}

void RootFrame::on_any_button_click(wxCommandEvent& evt)
{
    wxLogMessage("Wazaaaa");
}

void RootFrame::on_button1_click(wxCommandEvent& evt)
{
    wxLogStatus("button 1 clicked");
    evt.Skip();
}

void RootFrame::on_button2_click(wxCommandEvent& evt)
{
    wxLogStatus("button 2 clicked");
    evt.Skip();
}

