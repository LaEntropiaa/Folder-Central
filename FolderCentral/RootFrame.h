#ifndef ROOTFRAME_H
#define ROOTFRAME_H

#include <wx/wx.h>

class RootFrame : public wxFrame
{
private:
    void on_mouse_event(wxMouseEvent& evt);
public:
    int num = 0;
    RootFrame(const wxString& title);
};

#endif