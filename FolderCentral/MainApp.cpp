#include "MainApp.h"
#include "RootFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
    RootFrame* rootframe = new RootFrame("Test");
    rootframe->SetClientSize(800, 600);
    rootframe->Center();
    rootframe->Show();
    return true;
}
