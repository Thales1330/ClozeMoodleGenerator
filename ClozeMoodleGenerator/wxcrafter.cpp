//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: wxcrafter.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "wxcrafter.h"

// Declare the bitmap loading function
extern void wxC9ED9InitBitmapResources();

static bool bBitmapLoaded = false;

MainFrameBaseClass::MainFrameBaseClass(wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizerMain = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizerMain);

    m_ribbonBarMain = new wxRibbonBar(
        this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxRIBBON_BAR_DEFAULT_STYLE);
    m_ribbonBarMain->SetArtProvider(new wxRibbonAUIArtProvider);

    boxSizerMain->Add(m_ribbonBarMain, 0, wxEXPAND, WXC_FROM_DIP(5));

    m_ribbonPageMain = new wxRibbonPage(m_ribbonBarMain, wxID_ANY, wxT("Ferramentas"), wxNullBitmap, 0);
    m_ribbonBarMain->SetActivePage(m_ribbonPageMain);

    m_ribbonPanelFile = new wxRibbonPanel(m_ribbonPageMain, wxID_ANY, wxT("Arquivo"), wxNullBitmap, wxDefaultPosition,
        wxDLG_UNIT(m_ribbonPageMain, wxSize(-1, -1)), wxRIBBON_PANEL_DEFAULT_STYLE);

    m_ribbonButtonBarFile = new wxRibbonButtonBar(
        m_ribbonPanelFile, wxID_NEW, wxDefaultPosition, wxDLG_UNIT(m_ribbonPanelFile, wxSize(-1, -1)), 0);

    m_ribbonButtonBarFile->AddButton(wxID_NEW, wxT("Novo"), wxXmlResource::Get()->LoadBitmap(wxT("new")),
        wxT("Help String"), wxRIBBON_BUTTON_NORMAL);

    m_ribbonButtonBarFile->AddButton(
        wxID_SAVE, wxT("Salvar"), wxXmlResource::Get()->LoadBitmap(wxT("save")), wxT(""), wxRIBBON_BUTTON_NORMAL);

    m_ribbonButtonBarFile->AddButton(wxID_SAVEAS, wxT("Salvar Como..."),
        wxXmlResource::Get()->LoadBitmap(wxT("saveAs")), wxT(""), wxRIBBON_BUTTON_NORMAL);

    m_ribbonButtonBarFile->AddButton(
        wxID_OPEN, wxT("Abrir"), wxXmlResource::Get()->LoadBitmap(wxT("open")), wxT(""), wxRIBBON_BUTTON_NORMAL);

    m_ribbonButtonBarFile->AddButton(wxID_HARDDISK, wxT("Exportar"), wxXmlResource::Get()->LoadBitmap(wxT("export")),
        wxT(""), wxRIBBON_BUTTON_NORMAL);

    m_ribbonButtonBarFile->AddButton(
        wxID_EXIT, wxT("Sair"), wxXmlResource::Get()->LoadBitmap(wxT("close")), wxT(""), wxRIBBON_BUTTON_NORMAL);
    m_ribbonButtonBarFile->Realize();

    m_ribbonPanelTools = new wxRibbonPanel(m_ribbonPageMain, wxID_ANY, wxT("Ferramentas"), wxNullBitmap,
        wxDefaultPosition, wxDLG_UNIT(m_ribbonPageMain, wxSize(-1, -1)), wxRIBBON_PANEL_DEFAULT_STYLE);

    m_ribbonButtonBarTools = new wxRibbonButtonBar(
        m_ribbonPanelTools, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_ribbonPanelTools, wxSize(-1, -1)), 0);

    m_ribbonButtonBarTools->AddButton(wxID_ADD, wxT("Atualizar Entradas/Saídas"),
        wxXmlResource::Get()->LoadBitmap(wxT("input")), wxT(""), wxRIBBON_BUTTON_NORMAL);

    m_ribbonButtonBarTools->AddButton(wxID_EXECUTE, wxT("Interpretar Script"),
        wxXmlResource::Get()->LoadBitmap(wxT("runPy")), wxT(""), wxRIBBON_BUTTON_NORMAL);

    m_ribbonButtonBarTools->AddButton(wxID_VIEW_DETAILS, wxT("Pré-visualizar"),
        wxXmlResource::Get()->LoadBitmap(wxT("prweview")), wxT(""), wxRIBBON_BUTTON_NORMAL);
    m_ribbonButtonBarTools->Realize();

    m_ribbonPanelHelp = new wxRibbonPanel(m_ribbonPageMain, wxID_ANY, wxT("Ajuda"), wxNullBitmap, wxDefaultPosition,
        wxDLG_UNIT(m_ribbonPageMain, wxSize(-1, -1)), wxRIBBON_PANEL_DEFAULT_STYLE);

    m_ribbonButtonBarHelp = new wxRibbonButtonBar(
        m_ribbonPanelHelp, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_ribbonPanelHelp, wxSize(-1, -1)), 0);

    m_ribbonButtonBarHelp->AddButton(
        wxID_ABOUT, wxT("Sobre..."), wxXmlResource::Get()->LoadBitmap(wxT("about")), wxT(""), wxRIBBON_BUTTON_NORMAL);
    m_ribbonButtonBarHelp->Realize();
    m_ribbonBarMain->Realize();
    m_mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxTAB_TRAVERSAL);

    boxSizerMain->Add(m_mainPanel, 1, wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer_LVL1_1 = new wxBoxSizer(wxVERTICAL);
    m_mainPanel->SetSizer(boxSizer_LVL1_1);

    wxBoxSizer* boxSizer_LVL2_2 = new wxBoxSizer(wxHORIZONTAL);

    boxSizer_LVL1_1->Add(boxSizer_LVL2_2, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_notebookMain =
        new wxNotebook(m_mainPanel, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_mainPanel, wxSize(-1, -1)), wxBK_DEFAULT);
    m_notebookMain->SetName(wxT("m_notebookMain"));

    boxSizer_LVL2_2->Add(m_notebookMain, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_panelHTML = new wxPanel(
        m_notebookMain, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebookMain, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebookMain->AddPage(m_panelHTML, wxT("HTML"), true);

    wxBoxSizer* boxSizerLVL3_2 = new wxBoxSizer(wxVERTICAL);
    m_panelHTML->SetSizer(boxSizerLVL3_2);

    m_stcHTML =
        new wxStyledTextCtrl(m_panelHTML, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_panelHTML, wxSize(-1, -1)), 0);
    wxFont m_stcHTMLFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New"));
    m_stcHTML->SetFont(m_stcHTMLFont);
    // Configure the fold margin
    m_stcHTML->SetMarginType(4, wxSTC_MARGIN_SYMBOL);
    m_stcHTML->SetMarginMask(4, wxSTC_MASK_FOLDERS);
    m_stcHTML->SetMarginSensitive(4, true);
    m_stcHTML->SetMarginWidth(4, 16);

    m_stcHTML->SetProperty(wxT("fold"), wxT("1"));
    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_ARROWDOWN);
    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_ARROW);
    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_BACKGROUND);
    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_BACKGROUND);
    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_ARROW);
    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN);
    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_BACKGROUND);
    // Configure the tracker margin
    m_stcHTML->SetMarginWidth(1, 0);

    // Configure the symbol margin
    m_stcHTML->SetMarginType(2, wxSTC_MARGIN_SYMBOL);
    m_stcHTML->SetMarginMask(2, ~(wxSTC_MASK_FOLDERS));
    m_stcHTML->SetMarginWidth(2, 0);
    m_stcHTML->SetMarginSensitive(2, true);

    // Configure the line numbers margin
    int m_stcHTML_PixelWidth = 4 + 5 * m_stcHTML->TextWidth(wxSTC_STYLE_LINENUMBER, wxT("9"));
    m_stcHTML->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_stcHTML->SetMarginWidth(0, m_stcHTML_PixelWidth);

    // Configure the line symbol margin
    m_stcHTML->SetMarginType(3, wxSTC_MARGIN_FORE);
    m_stcHTML->SetMarginMask(3, 0);
    m_stcHTML->SetMarginWidth(3, 0);
    // Select the lexer
    m_stcHTML->SetLexer(wxSTC_LEX_HTML);
    // Set default font / styles
    m_stcHTML->StyleClearAll();
    for(int i = 0; i < wxSTC_STYLE_MAX; ++i) {
        m_stcHTML->StyleSetFont(i, m_stcHTMLFont);
    }
    m_stcHTML->SetWrapMode(1);
    m_stcHTML->SetIndentationGuides(1);
    m_stcHTML->SetKeyWords(0, wxT("def"));
    m_stcHTML->SetKeyWords(1, wxT("def"));
    m_stcHTML->SetKeyWords(2, wxT("def"));
    m_stcHTML->SetKeyWords(3, wxT("def"));
    m_stcHTML->SetKeyWords(4, wxT("def"));

    boxSizerLVL3_2->Add(m_stcHTML, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_panelPreview = new wxPanel(
        m_notebookMain, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebookMain, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebookMain->AddPage(m_panelPreview, wxT("Preview"), false);

    wxBoxSizer* boxSizerLVL3_3 = new wxBoxSizer(wxVERTICAL);
    m_panelPreview->SetSizer(boxSizerLVL3_3);

#if wxUSE_WEBVIEW
    m_webViewPreview = wxWebView::New(m_panelPreview, wxID_ANY, wxT("about:blank"), wxDefaultPosition,
        wxDLG_UNIT(m_panelPreview, wxSize(-1, -1)), wxWebViewBackendDefault, 0);

    boxSizerLVL3_3->Add(m_webViewPreview, 1, wxEXPAND, WXC_FROM_DIP(5));
#endif // wxUSE_WEBVIEW

    m_stcPython =
        new wxStyledTextCtrl(m_mainPanel, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_mainPanel, wxSize(-1, -1)), 0);
    wxFont m_stcPythonFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New"));
    m_stcPython->SetFont(m_stcPythonFont);
    // Configure the fold margin
    m_stcPython->SetMarginType(4, wxSTC_MARGIN_SYMBOL);
    m_stcPython->SetMarginMask(4, wxSTC_MASK_FOLDERS);
    m_stcPython->SetMarginSensitive(4, true);
    m_stcPython->SetMarginWidth(4, 16);

    m_stcPython->SetProperty(wxT("fold"), wxT("1"));
    m_stcPython->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_ARROWDOWN);
    m_stcPython->MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_ARROW);
    m_stcPython->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_BACKGROUND);
    m_stcPython->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_BACKGROUND);
    m_stcPython->MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_ARROW);
    m_stcPython->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN);
    m_stcPython->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_BACKGROUND);
    // Configure the tracker margin
    m_stcPython->SetMarginWidth(1, 0);

    // Configure the symbol margin
    m_stcPython->SetMarginType(2, wxSTC_MARGIN_SYMBOL);
    m_stcPython->SetMarginMask(2, ~(wxSTC_MASK_FOLDERS));
    m_stcPython->SetMarginWidth(2, 0);
    m_stcPython->SetMarginSensitive(2, true);

    // Configure the line numbers margin
    int m_stcPython_PixelWidth = 4 + 5 * m_stcPython->TextWidth(wxSTC_STYLE_LINENUMBER, wxT("9"));
    m_stcPython->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    m_stcPython->SetMarginWidth(0, m_stcPython_PixelWidth);

    // Configure the line symbol margin
    m_stcPython->SetMarginType(3, wxSTC_MARGIN_FORE);
    m_stcPython->SetMarginMask(3, 0);
    m_stcPython->SetMarginWidth(3, 0);
    // Select the lexer
    m_stcPython->SetLexer(wxSTC_LEX_PYTHON);
    // Set default font / styles
    m_stcPython->StyleClearAll();
    for(int i = 0; i < wxSTC_STYLE_MAX; ++i) {
        m_stcPython->StyleSetFont(i, m_stcPythonFont);
    }
    m_stcPython->SetWrapMode(1);
    m_stcPython->SetIndentationGuides(1);
    m_stcPython->SetKeyWords(0, wxT("def"));
    m_stcPython->SetKeyWords(1, wxT("def"));
    m_stcPython->SetKeyWords(2, wxT("def"));
    m_stcPython->SetKeyWords(3, wxT("def"));
    m_stcPython->SetKeyWords(4, wxT("def"));

    boxSizer_LVL2_2->Add(m_stcPython, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer_LVL2_1 = new wxBoxSizer(wxHORIZONTAL);

    boxSizer_LVL1_1->Add(boxSizer_LVL2_1, 0, wxEXPAND, WXC_FROM_DIP(5));

    m_gridInputs = new wxGrid(m_mainPanel, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_mainPanel, wxSize(300, 150)),
        wxWANTS_CHARS | wxALWAYS_SHOW_SB | wxBORDER_STATIC | wxVSCROLL);
    wxFont m_gridInputsFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Segoe UI"));
    m_gridInputs->SetFont(m_gridInputsFont);
    m_gridInputs->CreateGrid(0, 0);
    m_gridInputs->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    m_gridInputs->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
#if wxVERSION_NUMBER >= 2904
    m_gridInputs->UseNativeColHeader(true);
#endif
    m_gridInputs->EnableEditing(true);

    boxSizer_LVL2_1->Add(m_gridInputs, 0, wxALL, WXC_FROM_DIP(5));

    m_richTextCtrlConsole =
        new wxRichTextCtrl(m_mainPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(m_mainPanel, wxSize(-1, 150)),
            wxTE_READONLY | wxTE_MULTILINE | wxTE_PROCESS_TAB | wxTE_PROCESS_ENTER | wxWANTS_CHARS);
    m_richTextCtrlConsole->SetBackgroundColour(wxColour(wxT("rgb(84,18,63)")));
    m_richTextCtrlConsole->SetForegroundColour(wxColour(wxT("rgb(255,255,255)")));
    wxFont m_richTextCtrlConsoleFont(
        12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New"));
    m_richTextCtrlConsole->SetFont(m_richTextCtrlConsoleFont);

    boxSizer_LVL2_1->Add(m_richTextCtrlConsole, 1, wxALL, WXC_FROM_DIP(5));

    m_menuBar = new wxMenuBar(0);
    this->SetMenuBar(m_menuBar);

    m_nameFile = new wxMenu();
    m_menuBar->Append(m_nameFile, wxT("Arquivo"));

    m_menuItemNew = new wxMenuItem(m_nameFile, wxID_NEW, wxT("Novo\tCtrl-N"), wxT(""), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemNew);

    m_menuItemSave = new wxMenuItem(m_nameFile, wxID_SAVE, wxT("Salvar\tCtrl-S"), wxT(""), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemSave);

    m_menuItemSaveAs =
        new wxMenuItem(m_nameFile, wxID_SAVEAS, wxT("Salvar Como...\tCtrl-Shift-S"), wxT(""), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemSaveAs);

    m_menuItemOpen = new wxMenuItem(m_nameFile, wxID_OPEN, wxT("Abrir\tCtrl-O"), wxT(""), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemOpen);

    m_menuItemExport = new wxMenuItem(m_nameFile, wxID_CONVERT, wxT("Exportar\tCtrl-E"), wxT(""), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemExport);

    m_menuItemExit = new wxMenuItem(m_nameFile, wxID_EXIT, wxT("Sair\tAlt-X"), wxT("Quit"), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemExit);

    m_nameHelp = new wxMenu();
    m_menuBar->Append(m_nameHelp, wxT("Ajuda"));

    m_menuItemAbout = new wxMenuItem(m_nameHelp, wxID_ABOUT, wxT("Sobre..."), wxT(""), wxITEM_NORMAL);
    m_nameHelp->Append(m_menuItemAbout);

#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(m_notebookMain)) {
        wxPersistenceManager::Get().RegisterAndRestore(m_notebookMain);
    } else {
        wxPersistenceManager::Get().Restore(m_notebookMain);
    }
#endif

    SetName(wxT("MainFrameBaseClass"));
    SetMinClientSize(wxSize(1280, 720));
    SetSize(wxDLG_UNIT(this, wxSize(1280, 720)));
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
    // Connect events
    this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainFrameBaseClass::OnWindowClose), NULL, this);
    m_ribbonButtonBarFile->Connect(wxID_NEW, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnNewRibbonClick), NULL, this);
    m_ribbonButtonBarFile->Connect(wxID_SAVE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnSaveRibbonClick), NULL, this);
    m_ribbonButtonBarFile->Connect(wxID_SAVEAS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnSaveAsRibbonClick), NULL, this);
    m_ribbonButtonBarFile->Connect(wxID_OPEN, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnOpenRibbonClick), NULL, this);
    m_ribbonButtonBarFile->Connect(wxID_HARDDISK, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnExportRibbonClick), NULL, this);
    m_ribbonButtonBarFile->Connect(wxID_EXIT, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnQuitRibbonClick), NULL, this);
    m_ribbonButtonBarTools->Connect(wxID_ADD, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnGetInputRibbonClick), NULL, this);
    m_ribbonButtonBarTools->Connect(wxID_EXECUTE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnRunPyRibbonClick), NULL, this);
    m_ribbonButtonBarTools->Connect(wxID_VIEW_DETAILS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnPreviewRibbonClick), NULL, this);
    m_ribbonButtonBarHelp->Connect(wxID_ABOUT, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OAboutRibbonClick), NULL, this);
    m_stcHTML->Connect(
        wxEVT_STC_INDICATOR_CLICK, wxStyledTextEventHandler(MainFrameBaseClass::OnIndicatorClick), NULL, this);
    m_stcHTML->Connect(wxEVT_STC_MARGINCLICK, wxStyledTextEventHandler(MainFrameBaseClass::OnMarginClick), NULL, this);
#if wxUSE_WEBVIEW

#endif // wxUSE_WEBVIEW
    m_gridInputs->Connect(
        wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(MainFrameBaseClass::OnCellDataChanged), NULL, this);
    m_gridInputs->Connect(wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(MainFrameBaseClass::OnLeftClick), NULL, this);
    this->Connect(m_menuItemNew->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnNewClick), NULL, this);
    this->Connect(m_menuItemSave->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnSaveClick), NULL, this);
    this->Connect(m_menuItemSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnSaveAsClick), NULL, this);
    this->Connect(m_menuItemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnOpenClick), NULL, this);
    this->Connect(m_menuItemExport->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnExportClick), NULL, this);
    this->Connect(m_menuItemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnExit), NULL, this);
    this->Connect(m_menuItemAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnAbout), NULL, this);
}

MainFrameBaseClass::~MainFrameBaseClass()
{
    this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainFrameBaseClass::OnWindowClose), NULL, this);
    m_ribbonButtonBarFile->Disconnect(wxID_NEW, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnNewRibbonClick), NULL, this);
    m_ribbonButtonBarFile->Disconnect(wxID_SAVE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnSaveRibbonClick), NULL, this);
    m_ribbonButtonBarFile->Disconnect(wxID_SAVEAS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnSaveAsRibbonClick), NULL, this);
    m_ribbonButtonBarFile->Disconnect(wxID_OPEN, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnOpenRibbonClick), NULL, this);
    m_ribbonButtonBarFile->Disconnect(wxID_HARDDISK, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnExportRibbonClick), NULL, this);
    m_ribbonButtonBarFile->Disconnect(wxID_EXIT, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnQuitRibbonClick), NULL, this);
    m_ribbonButtonBarTools->Disconnect(wxID_ADD, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnGetInputRibbonClick), NULL, this);
    m_ribbonButtonBarTools->Disconnect(wxID_EXECUTE, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnRunPyRibbonClick), NULL, this);
    m_ribbonButtonBarTools->Disconnect(wxID_VIEW_DETAILS, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OnPreviewRibbonClick), NULL, this);
    m_ribbonButtonBarHelp->Disconnect(wxID_ABOUT, wxEVT_COMMAND_RIBBONBUTTON_CLICKED,
        wxRibbonButtonBarEventHandler(MainFrameBaseClass::OAboutRibbonClick), NULL, this);
    m_stcHTML->Disconnect(
        wxEVT_STC_INDICATOR_CLICK, wxStyledTextEventHandler(MainFrameBaseClass::OnIndicatorClick), NULL, this);
    m_stcHTML->Disconnect(
        wxEVT_STC_MARGINCLICK, wxStyledTextEventHandler(MainFrameBaseClass::OnMarginClick), NULL, this);
#if wxUSE_WEBVIEW

#endif // wxUSE_WEBVIEW
    m_gridInputs->Disconnect(
        wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(MainFrameBaseClass::OnCellDataChanged), NULL, this);
    m_gridInputs->Disconnect(
        wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(MainFrameBaseClass::OnLeftClick), NULL, this);
    this->Disconnect(m_menuItemNew->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnNewClick), NULL, this);
    this->Disconnect(m_menuItemSave->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnSaveClick), NULL, this);
    this->Disconnect(m_menuItemSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnSaveAsClick), NULL, this);
    this->Disconnect(m_menuItemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnOpenClick), NULL, this);
    this->Disconnect(m_menuItemExport->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnExportClick), NULL, this);
    this->Disconnect(m_menuItemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnExit), NULL, this);
    this->Disconnect(m_menuItemAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainFrameBaseClass::OnAbout), NULL, this);
}

HTMLPreviewBase::HTMLPreviewBase(wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizerMain = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizerMain);

#if wxUSE_WEBVIEW
    m_webView = wxWebView::New(this, wxID_ANY, wxT("about:blank"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)),
        wxWebViewBackendDefault, 0);

    boxSizerMain->Add(m_webView, 1, wxEXPAND, WXC_FROM_DIP(5));
#endif // wxUSE_WEBVIEW

    SetName(wxT("HTMLPreviewBase"));
    SetSize(wxDLG_UNIT(this, wxSize(800, 600)));
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
// Connect events
#if wxUSE_WEBVIEW

#endif // wxUSE_WEBVIEW
}

HTMLPreviewBase::~HTMLPreviewBase()
{
#if wxUSE_WEBVIEW

#endif // wxUSE_WEBVIEW
}

ExportCloseBase::ExportCloseBase(wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9ED9InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizerMain = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizerMain);

    wxBoxSizer* boxSizerLVL1_1 = new wxBoxSizer(wxVERTICAL);

    boxSizerMain->Add(boxSizerLVL1_1, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticTextCatName = new wxStaticText(
        this, wxID_ANY, wxT("Nome da categoria"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizerLVL1_1->Add(m_staticTextCatName, 0, wxLEFT | wxRIGHT | wxTOP, WXC_FROM_DIP(5));

    m_textCtrlCatName = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlCatName->SetHint(wxT("Provinha_2021-1"));
#endif

    boxSizerLVL1_1->Add(m_textCtrlCatName, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, WXC_FROM_DIP(5));

    m_staticTextNumQuiz = new wxStaticText(
        this, wxID_ANY, wxT("Número de questões"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizerLVL1_1->Add(m_staticTextNumQuiz, 0, wxLEFT | wxRIGHT | wxTOP, WXC_FROM_DIP(5));

    m_textCtrlNumQuiz = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlNumQuiz->SetHint(wxT("30"));
#endif

    boxSizerLVL1_1->Add(m_textCtrlNumQuiz, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizerLVL2_1 = new wxBoxSizer(wxHORIZONTAL);

    boxSizerLVL1_1->Add(boxSizerLVL2_1, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(5));

    m_buttonExportar =
        new wxButton(this, wxID_ANY, wxT("Exportar"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizerLVL2_1->Add(m_buttonExportar, 0, wxALL, WXC_FROM_DIP(5));

    m_buttonCancel =
        new wxButton(this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizerLVL2_1->Add(m_buttonCancel, 0, wxALL, WXC_FROM_DIP(5));

    SetName(wxT("ExportCloseBase"));
    SetSize(wxDLG_UNIT(this, wxSize(500, 300)));
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
    // Connect events
    m_buttonExportar->Connect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ExportCloseBase::OnExportClick), NULL, this);
    m_buttonCancel->Connect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ExportCloseBase::OnCancelClick), NULL, this);
}

ExportCloseBase::~ExportCloseBase()
{
    m_buttonExportar->Disconnect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ExportCloseBase::OnExportClick), NULL, this);
    m_buttonCancel->Disconnect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ExportCloseBase::OnCancelClick), NULL, this);
}
