#ifndef ROOTFRAME_H
#define ROOTFRAME_H

#include <wx/wx.h>

class RootFrame : public wxFrame
{
private:
    void on_button_click(wxCommandEvent& evt);
    void on_slider_move(wxCommandEvent& evt);
    void on_text_change(wxCommandEvent& evt);
public:
    RootFrame(const wxString& title);
};

#endif