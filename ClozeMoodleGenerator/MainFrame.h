#ifndef MAINFRAME_H
#define MAINFRAME_H

//#define WXINTL_NO_GETTEXT_MACRO 1
#define PY_SSIZE_T_CLEAN

#include "wxcrafter.h"

#include "pyhelper.h"
#include <utility>
#include <random>
#include <wx/textfile.h>
#include "ArtMetro.h"

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
    int offset = 0;
    double start = 0.0;
    double end = 0.0;
    double stdValue = 0.0;
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
    virtual void OnNewRibbonClick(wxRibbonButtonBarEvent& event);
    virtual void OnNewClick(wxCommandEvent& event);
    virtual void OnWindowClose(wxCloseEvent& event);
    virtual void OAboutRibbonClick(wxRibbonButtonBarEvent& event);
    virtual void OnExportRibbonClick(wxRibbonButtonBarEvent& event);
    virtual void OnGetInputRibbonClick(wxRibbonButtonBarEvent& event);
    virtual void OnOpenRibbonClick(wxRibbonButtonBarEvent& event);
    virtual void OnPreviewRibbonClick(wxRibbonButtonBarEvent& event);
    virtual void OnQuitRibbonClick(wxRibbonButtonBarEvent& event);
    virtual void OnRunPyRibbonClick(wxRibbonButtonBarEvent& event);
    virtual void OnSaveAsRibbonClick(wxRibbonButtonBarEvent& event);
    virtual void OnSaveRibbonClick(wxRibbonButtonBarEvent& event);
    virtual void OnMarginClick(wxStyledTextEvent& event);
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
    void SendToConsole(wxString str, wxColour textColour = wxColour(255, 255, 255));
    PyObject* LoadPyModule(wxCStrData script, std::vector<wxString> &errors);
    void RunPythonScript(std::vector<wxString> inputs, PyObject* pModule, double &returnValue, std::vector<wxString> &errors);
    void FillTable();
    void ExportXMLToFile(int numQuiz, wxString catName, wxString path);
    double GetRandom(double init, double end);
    wxString GetStrSave();
    void OpenFile(wxTextFile& file);
    void FormatHTML();
    
    void GenerateNewRandomInputValues();
    bool CalculateOutputs(bool useInputValue = true);
    wxString GetHTMLFromCurrentIOs();
    
    wxRibbonMetroArtProvider* m_artMetro = nullptr;
    
    const wxColour m_dfltConsoleBackColour = wxColour(84, 18, 63);
    const wxColour m_dfltConsoleTextColour = wxColour(255, 255, 255);
    unsigned int m_numNonASCIICh = 0;
    
    std::vector<IOTag> m_ioTagList;
    std::vector<IOTag> m_ioTagTable;
    int m_highlightID = wxID_ANY;
    
    std::default_random_engine m_rndGenerator;
    
    // File
    wxString m_filePath = "";
};
#endif // MAINFRAME_H
