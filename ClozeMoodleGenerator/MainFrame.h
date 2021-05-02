#ifndef MAINFRAME_H
#define MAINFRAME_H

//#define WXINTL_NO_GETTEXT_MACRO 1
#define PY_SSIZE_T_CLEAN

#include "wxcrafter.h"

#include "pyhelper.h"
#include <utility>
#include <random>
#include <wx/textfile.h>

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
    double value = 0.0;
};


class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
protected:
    virtual void OnOpenClick(wxCommandEvent& event);
    virtual void OnSaveAsClick(wxCommandEvent& event);
    virtual void OnSaveClick(wxCommandEvent& event);
    virtual void OnExportClick(wxCommandEvent& event);
    virtual void OnCellDataChanged(wxGridEvent& event);
    virtual void OnLeftClick(wxGridEvent& event);
    virtual void OnIndicatorClick(wxStyledTextEvent& event);
    virtual void GetInput(wxCommandEvent& event);
    virtual void OnPreviewClick(wxCommandEvent& event);
    virtual void OnIntClick(wxCommandEvent& event);
    void SendToConsole(wxString str, wxColour backColour = wxColour(0, 120, 215));
    void RunPythonScript(std::vector<wxString> inputs, wxCStrData script, double &returnValue, std::vector<wxString> &errors);
    void FillTable();
    void ExportXMLToFile(int numQuiz, wxString catName, wxString path);
    double GetRandom(double init, double end);
    wxString GetStrSave();
    void OpenFile(wxTextFile& file);
    
    void GenerateNewRandomInputValues();
    bool CalculateOutputs(bool useInputValue = true);
    wxString GetHTMLFromCurrentIOs();
    
    const wxColour m_dfltConsoleBackColour = wxColour(0, 120, 215);
    
    std::vector<IOTag> m_ioTagList;
    std::vector<IOTag> m_ioTagTable;
    int m_highlightID = wxID_ANY;
    
    std::default_random_engine m_rndGenerator;
    
    // File
    wxString m_filePath = "";
};
#endif // MAINFRAME_H
