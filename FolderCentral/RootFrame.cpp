#include "RootFrame.h"
#include <wx\wx.h>
#include <wx/spinctrl.h>

RootFrame::RootFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel* panel = new wxPanel(this);

    wxButton* button = new wxButton(panel, wxID_ANY, "Boton", wxPoint(180, 60), wxSize(100, 40), wxBU_EXACTFIT);

    wxCheckBox* checkbox = new wxCheckBox(panel, wxID_ANY, "Boxes", wxPoint(180, 140));

    wxStaticText* txt = new wxStaticText(panel, wxID_ANY, "I'm kendrick llama cuuuuh", wxPoint(180, 220));

    wxTextCtrl* txtctrl = new wxTextCtrl(panel, wxID_ANY, "Editable?", wxPoint(180, 350), wxSize(200, -1));

    wxSlider* slider = new wxSlider(panel, wxID_ANY, 25, 0, 100, wxPoint(180, 490), wxSize(200, -1));

    wxGauge* gauge = new wxGauge(panel, wxID_ANY, 1000, wxPoint(500, 60), wxSize(200, -1));
    gauge->SetValue(455);

    wxArrayString choices;
    choices.Add("A");
    choices.Add("B");
    choices.Add("C");
    choices.Add("D");

    wxChoice* choice = new wxChoice(panel, wxID_ANY, wxPoint(500, 140), wxSize(200, -1), choices);
    choice->Select(0);

    wxSpinCtrl* spin = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(500, 220), wxDefaultSize, 16384L, 0, 17, 1);

    wxListBox* list = new wxListBox(panel, wxID_ANY, wxPoint(500, 350), wxSize(100, -1), choices);

    wxRadioBox* rad = new wxRadioBox(panel, wxID_ANY, wxString("RadioBox"), wxPoint(450, 490), wxDefaultSize, choices);
}
