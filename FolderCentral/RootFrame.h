#ifndef ROOTFRAME_H
#define ROOTFRAME_H

#include <wx/wx.h>

class RootFrame : public wxFrame
{
private:
    void on_any_button_click(wxCommandEvent& evt);
    void on_button1_click(wxCommandEvent& evt);
    void on_button2_click(wxCommandEvent& evt);
public:
    RootFrame(const wxString& title);
};

#endif