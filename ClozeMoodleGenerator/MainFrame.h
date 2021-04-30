#ifndef MAINFRAME_H
#define MAINFRAME_H

//#define WXINTL_NO_GETTEXT_MACRO 1
#define PY_SSIZE_T_CLEAN

#include "wxcrafter.h"

#include "pyhelper.h"
#include <utility>

enum class IOTagType
{
    input,
    output
};

struct IOTag
{
    IOTagType type = IOTagType::input;
    wxString name = "";
    std::pair<int, int> position = std::make_pair(0,0);
    double start, end, stdValue = 0.0;
    int decimalPlaces = 2;
    double result = 0.0;
};


class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
protected:
    virtual void OnExportClick(wxCommandEvent& event);
    virtual void OnCellDataChanged(wxGridEvent& event);
    virtual void OnLeftClick(wxGridEvent& event);
    virtual void OnIndicatorClick(wxStyledTextEvent& event);
    virtual void GetInput(wxCommandEvent& event);
    virtual void OnPreviewClick(wxCommandEvent& event);
    virtual void OnIntClick(wxCommandEvent& event);
    void SendToConsole(wxString str);
    void RunPythonScript(std::vector<wxString> inputs, wxCStrData script, double &returnValue, std::vector<wxString> &errors);
    void FillTable();
    void ExportXMLToFile(int numQuiz, wxString catName, wxString path, wxString filename);
    
    std::vector<IOTag> m_ioTagList;
    std::vector<IOTag> m_ioTagTable;
    int m_highlightID = wxID_ANY;
};
#endif // MAINFRAME_H
