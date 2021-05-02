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

    m_mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), wxTAB_TRAVERSAL);

    boxSizerMain->Add(m_mainPanel, 1, wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer_LVL1_1 = new wxBoxSizer(wxHORIZONTAL);
    m_mainPanel->SetSizer(boxSizer_LVL1_1);

    wxBoxSizer* boxSizer_LVL2_2 = new wxBoxSizer(wxVERTICAL);

    boxSizer_LVL1_1->Add(boxSizer_LVL2_2, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_stcHTML =
        new wxStyledTextCtrl(m_mainPanel, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_mainPanel, wxSize(-1, -1)), 0);
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

    boxSizer_LVL2_2->Add(m_stcHTML, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_buttonGetInput = new wxButton(
        m_mainPanel, wxID_ANY, _("Obter entradas"), wxDefaultPosition, wxDLG_UNIT(m_mainPanel, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 2904
    m_buttonGetInput->SetBitmap(wxArtProvider::GetBitmap(wxART_GO_DOWN, wxART_TOOLBAR, wxDefaultSize), wxLEFT);
    m_buttonGetInput->SetBitmapMargins(2, 2);
#endif

    boxSizer_LVL2_2->Add(m_buttonGetInput, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(5));

    m_gridInputs = new wxGrid(m_mainPanel, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_mainPanel, wxSize(-1, 200)),
        wxWANTS_CHARS | wxALWAYS_SHOW_SB | wxBORDER_STATIC | wxVSCROLL);
    wxFont m_gridInputsFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Segoe UI"));
    m_gridInputs->SetFont(m_gridInputsFont);
    m_gridInputs->CreateGrid(0, 0);
    m_gridInputs->SetRowLabelAlignment(wxALIGN_RIGHT, wxALIGN_CENTRE);
    m_gridInputs->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
#if wxVERSION_NUMBER >= 2904
    m_gridInputs->UseNativeColHeader(true);
#endif
    m_gridInputs->EnableEditing(true);

    boxSizer_LVL2_2->Add(m_gridInputs, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer_LVL2_1 = new wxBoxSizer(wxVERTICAL);

    boxSizer_LVL1_1->Add(boxSizer_LVL2_1, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

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

    boxSizer_LVL2_1->Add(m_stcPython, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_richTextCtrlConsole =
        new wxRichTextCtrl(m_mainPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(m_mainPanel, wxSize(-1, -1)),
            wxTE_READONLY | wxTE_MULTILINE | wxTE_PROCESS_TAB | wxTE_PROCESS_ENTER | wxWANTS_CHARS);
    m_richTextCtrlConsole->SetBackgroundColour(wxColour(wxT("rgb(0,120,215)")));
    m_richTextCtrlConsole->SetForegroundColour(wxColour(wxT("rgb(255,255,255)")));
    wxFont m_richTextCtrlConsoleFont(
        12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New"));
    m_richTextCtrlConsole->SetFont(m_richTextCtrlConsoleFont);

    boxSizer_LVL2_1->Add(m_richTextCtrlConsole, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer_LVL3_1 = new wxBoxSizer(wxHORIZONTAL);

    boxSizer_LVL2_1->Add(boxSizer_LVL3_1, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(5));

    m_buttonRunPy = new wxButton(
        m_mainPanel, wxID_ANY, _("Interpretar Script"), wxDefaultPosition, wxDLG_UNIT(m_mainPanel, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 2904
    m_buttonRunPy->SetBitmap(wxArtProvider::GetBitmap(wxART_HELP_SIDE_PANEL, wxART_TOOLBAR, wxDefaultSize), wxLEFT);
    m_buttonRunPy->SetBitmapMargins(2, 2);
#endif

    boxSizer_LVL3_1->Add(m_buttonRunPy, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_buttonRunPreview = new wxButton(
        m_mainPanel, wxID_ANY, _("Preview"), wxDefaultPosition, wxDLG_UNIT(m_mainPanel, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 2904
    m_buttonRunPreview->SetBitmap(wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_TOOLBAR, wxDefaultSize), wxLEFT);
    m_buttonRunPreview->SetBitmapMargins(2, 2);
#endif

    boxSizer_LVL3_1->Add(
        m_buttonRunPreview, 0, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_menuBar = new wxMenuBar(0);
    this->SetMenuBar(m_menuBar);

    m_nameFile = new wxMenu();
    m_menuBar->Append(m_nameFile, _("Arquivo"));

    m_menuItemSave = new wxMenuItem(m_nameFile, wxID_SAVE, _("Salvar\tCtrl-S"), wxT(""), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemSave);

    m_menuItemSaveAs =
        new wxMenuItem(m_nameFile, wxID_SAVEAS, _("Salvar Como...\tCtrl-Shift-S"), wxT(""), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemSaveAs);

    m_menuItemOpen = new wxMenuItem(m_nameFile, wxID_OPEN, _("Abrir\tCtrl-O"), wxT(""), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemOpen);

    m_menuItemExport = new wxMenuItem(m_nameFile, wxID_CONVERT, _("Exportar\tCtrl-E"), wxT(""), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemExport);

    m_menuItemExit = new wxMenuItem(m_nameFile, wxID_EXIT, _("Sair\tAlt-X"), _("Quit"), wxITEM_NORMAL);
    m_nameFile->Append(m_menuItemExit);

    m_nameHelp = new wxMenu();
    m_menuBar->Append(m_nameHelp, _("Ajuda"));

    m_menuItemAbout = new wxMenuItem(m_nameHelp, wxID_ABOUT, _("Sobre..."), wxT(""), wxITEM_NORMAL);
    m_nameHelp->Append(m_menuItemAbout);

    m_mainToolbar = this->CreateToolBar(wxTB_FLAT, wxID_ANY);
    m_mainToolbar->SetToolBitmapSize(wxSize(16, 16));

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
    m_stcHTML->Connect(
        wxEVT_STC_INDICATOR_CLICK, wxStyledTextEventHandler(MainFrameBaseClass::OnIndicatorClick), NULL, this);
    m_buttonGetInput->Connect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBaseClass::GetInput), NULL, this);
    m_gridInputs->Connect(
        wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(MainFrameBaseClass::OnCellDataChanged), NULL, this);
    m_gridInputs->Connect(wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(MainFrameBaseClass::OnLeftClick), NULL, this);
    m_buttonRunPy->Connect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnIntClick), NULL, this);
    m_buttonRunPreview->Connect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnPreviewClick), NULL, this);
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
    m_stcHTML->Disconnect(
        wxEVT_STC_INDICATOR_CLICK, wxStyledTextEventHandler(MainFrameBaseClass::OnIndicatorClick), NULL, this);
    m_buttonGetInput->Disconnect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBaseClass::GetInput), NULL, this);
    m_gridInputs->Disconnect(
        wxEVT_GRID_CELL_CHANGED, wxGridEventHandler(MainFrameBaseClass::OnCellDataChanged), NULL, this);
    m_gridInputs->Disconnect(
        wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(MainFrameBaseClass::OnLeftClick), NULL, this);
    m_buttonRunPy->Disconnect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnIntClick), NULL, this);
    m_buttonRunPreview->Disconnect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBaseClass::OnPreviewClick), NULL, this);
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
    m_webView = wxWebView::New(this, wxID_ANY, _("about:blank"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)),
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
        this, wxID_ANY, _("Nome da categoria"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizerLVL1_1->Add(m_staticTextCatName, 0, wxLEFT | wxRIGHT | wxTOP, WXC_FROM_DIP(5));

    m_textCtrlCatName = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlCatName->SetHint(_("Provinha_2021-1"));
#endif

    boxSizerLVL1_1->Add(m_textCtrlCatName, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, WXC_FROM_DIP(5));

    m_staticTextNumQuiz = new wxStaticText(
        this, wxID_ANY, _("Número de questões"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizerLVL1_1->Add(m_staticTextNumQuiz, 0, wxLEFT | wxRIGHT | wxTOP, WXC_FROM_DIP(5));

    m_textCtrlNumQuiz = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlNumQuiz->SetHint(_("30"));
#endif

    boxSizerLVL1_1->Add(m_textCtrlNumQuiz, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizerLVL2_1 = new wxBoxSizer(wxHORIZONTAL);

    boxSizerLVL1_1->Add(boxSizerLVL2_1, 1, wxALL | wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(5));

    m_buttonExportar =
        new wxButton(this, wxID_ANY, _("Exportar"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizerLVL2_1->Add(m_buttonExportar, 0, wxALL, WXC_FROM_DIP(5));

    m_buttonCancel =
        new wxButton(this, wxID_ANY, _("Cancelar"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

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
