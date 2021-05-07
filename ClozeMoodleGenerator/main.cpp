#define WXINTL_NO_GETTEXTclTabCtrl_MACRO 1

//#include <Python.h>
//#include <pybind11/embed.h>

#include "MainFrame.h"
#include <wx/app.h>
#include <wx/event.h>
#include <wx/fs_mem.h>
#include <wx/image.h>
#include <wx/log.h>
#include <wx/webviewfshandler.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

// Define the MainApp
class MainApp : public wxApp
{
public:
    MainApp()
    {
    }
    virtual ~MainApp()
    {
    }

    virtual bool OnInit()
    {
        // Add the common image handlers
        wxImage::AddHandler(new wxPNGHandler);
        wxImage::AddHandler(new wxJPEGHandler);

        // wxLog::SetActiveTarget(new wxLogStream());
        wxFileSystem::AddHandler(new wxMemoryFSHandler);

        wxLocale* locale = new wxLocale();
        locale->Init(locale->GetSystemLanguage(), wxLOCALE_LOAD_DEFAULT);

        MainFrame* mainFrame = new MainFrame(NULL);
        SetTopWindow(mainFrame);
        mainFrame->SetIcon(wxICON(aaaa));
        return GetTopWindow()->Show();
    }
};

DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)
