#include "MainFrame.h"
#include "STDCapture.h"
#include <random>
#include <sstream>
#include <vector>
#include <wx/aboutdlg.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/tokenzr.h>
#include <wx/webviewfshandler.h>

#include "ExportClose.h"
#include "XMLParser.h"

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    m_rndGenerator.seed(time(0));
    SetTitle(wxT("Gerador de questões"));
    SetSize(GetBestSize());

    // Translation problems

    m_artMetro = new wxRibbonMetroArtProvider();
    m_ribbonBarMain->SetArtProvider(m_artMetro);
    m_ribbonBarMain->Realize();

    m_stcPython->StyleClearAll();
    m_stcPython->SetLexer(wxSTC_LEX_PYTHON);

    wxString source = "#Escreva o script em python aqui!\n\ndef soma(a, b):\n\treturn a + b";

    m_stcPython->SetText(source);

    m_stcPython->StyleSetForeground(wxSTC_P_STRING, wxColour(150, 0, 0));
    m_stcPython->StyleSetForeground(wxSTC_P_IDENTIFIER, wxColour(40, 0, 60));
    m_stcPython->StyleSetForeground(wxSTC_P_NUMBER, wxColour(0, 150, 0));
    m_stcPython->StyleSetForeground(wxSTC_P_CHARACTER, wxColour(150, 0, 0));
    m_stcPython->StyleSetForeground(wxSTC_P_OPERATOR, wxColour(150, 0, 150));
    m_stcPython->StyleSetForeground(wxSTC_P_WORD, wxColour(0, 0, 150));
    m_stcPython->StyleSetForeground(wxSTC_P_WORD2, wxColour(255, 165, 0));
    m_stcPython->StyleSetForeground(wxSTC_P_COMMENTLINE, wxColour(150, 150, 150));
    m_stcPython->StyleSetBold(wxSTC_P_WORD, true);
    m_stcPython->StyleSetBold(wxSTC_P_WORD2, true);
    // m_stc->StyleSetBold(wxSTC_P_COMMENTDOCKEYWORD, true);
    m_stcPython->SetTabWidth(3);

    m_stcPython->SetKeyWords(0,
        wxT("False None True __peg_parser__ and as assert async await break class continue def del elif else except "
            "finally for from global if import in is lambda nonlocal not or pass raise return try while with yield"));
    m_stcPython->SetKeyWords(1, wxT("const int float void char double str"));

    m_stcHTML->StyleClearAll();
    m_stcHTML->SetLexer(wxSTC_LEX_HTML);

    m_stcHTML->StyleSetForeground(wxSTC_H_COMMENT, wxColour(150, 150, 150));
    m_stcHTML->StyleSetForeground(wxSTC_H_DOUBLESTRING, wxColour(255, 0, 0));
    m_stcHTML->StyleSetForeground(wxSTC_H_SINGLESTRING, wxColour(255, 0, 0));
    m_stcHTML->StyleSetForeground(wxSTC_H_ENTITY, wxColour(255, 0, 0));
    m_stcHTML->StyleSetForeground(wxSTC_H_TAG, wxColour(0, 150, 0));
    m_stcHTML->StyleSetForeground(wxSTC_H_TAGUNKNOWN, wxColour(0, 150, 0));
    m_stcHTML->StyleSetForeground(wxSTC_H_ATTRIBUTE, wxColour(0, 0, 150));
    m_stcHTML->StyleSetForeground(wxSTC_H_ATTRIBUTEUNKNOWN, wxColour(0, 0, 150));

    m_stcHTML->IndicatorSetUnder(10, true);
    m_stcHTML->IndicatorSetStyle(10, wxSTC_INDIC_ROUNDBOX);
    ////m_stcHTML->IndicatorSetHoverStyle(m_highlightID, wxSTC_INDIC_ROUNDBOX);
    m_stcHTML->IndicatorSetAlpha(10, 200);
    m_stcHTML->IndicatorSetUnder(10, true);
    m_stcHTML->IndicatorSetForeground(10, wxColor(255, 85, 0));
    m_stcHTML->SetIndicatorCurrent(10);

    // FOLD
    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUSCONNECTED);
    m_stcHTML->MarkerSetForeground(wxSTC_MARKNUM_FOLDEREND, wxColor(243, 243, 243));
    m_stcHTML->MarkerSetBackground(wxSTC_MARKNUM_FOLDEREND, wxColor(128, 128, 128));

    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUSCONNECTED);
    m_stcHTML->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPENMID, wxColor(243, 243, 243));
    m_stcHTML->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPENMID, wxColor(128, 128, 128));

    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_TCORNER);
    m_stcHTML->MarkerSetForeground(wxSTC_MARKNUM_FOLDERMIDTAIL, wxColor(243, 243, 243));
    m_stcHTML->MarkerSetBackground(wxSTC_MARKNUM_FOLDERMIDTAIL, wxColor(128, 128, 128));

    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_LCORNER);
    m_stcHTML->MarkerSetForeground(wxSTC_MARKNUM_FOLDERTAIL, wxColor(243, 243, 243));
    m_stcHTML->MarkerSetBackground(wxSTC_MARKNUM_FOLDERTAIL, wxColor(128, 128, 128));

    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_VLINE);
    m_stcHTML->MarkerSetForeground(wxSTC_MARKNUM_FOLDERSUB, wxColor(243, 243, 243));
    m_stcHTML->MarkerSetBackground(wxSTC_MARKNUM_FOLDERSUB, wxColor(128, 128, 128));

    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS);
    m_stcHTML->MarkerSetForeground(wxSTC_MARKNUM_FOLDER, wxColor(243, 243, 243));
    m_stcHTML->MarkerSetBackground(wxSTC_MARKNUM_FOLDER, wxColor(128, 128, 128));

    m_stcHTML->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS);
    m_stcHTML->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPEN, wxColor(243, 243, 243));
    m_stcHTML->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPEN, wxColor(128, 128, 128));

    m_stcHTML->SetFoldMarginColour(true, wxColor(255, 255, 255));
    m_stcHTML->SetFoldMarginHiColour(true, wxColor(233, 233, 233));

    m_stcHTML->SetText("<!-- Cole o HTML do Moodle aqui! -->\n[[+t1]] + [[+t2]] = [[-soma t1 t2]]");

    auto style = m_richTextCtrlConsole->GetBasicStyle();
    style.SetTextColour(*wxWHITE);
    style.SetBackgroundColour(m_dfltConsoleBackColour);
    m_richTextCtrlConsole->SetBasicStyle(style);

    m_gridInputs->SetDefaultColSize(200);
    m_gridInputs->SetDefaultCellFont(wxFont(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    m_gridInputs->SetLabelFont(wxFont(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    m_gridInputs->AppendCols(5);
    m_gridInputs->SetColLabelValue(0, wxT("Nome"));
    m_gridInputs->SetColLabelValue(1, wxT("Inicial"));
    m_gridInputs->SetColLabelValue(2, wxT("Final"));
    m_gridInputs->SetColLabelValue(3, wxT("Padrão"));
    m_gridInputs->SetColLabelValue(4, wxT("Casas decimais"));
    m_gridInputs->SetSelectionBackground(wxColour(51, 153, 255));
    m_gridInputs->SetSelectionForeground(wxColour(255, 51, 0));
    m_gridInputs->SetSelectionMode(wxGrid::wxGridSelectCells);
    m_gridInputs->HideRowLabels();

    m_gridInputs->EnableCellEditControl();

    m_gridInputs->AutoSize();
    m_gridInputs->Layout();
    m_mainPanel->Layout();

    Py_Initialize();
}

MainFrame::~MainFrame()
{
    Py_FinalizeEx();
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{

    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.AddDeveloper(wxT("Thales Lima Oliveira"));
    info.SetLicence(wxT("GPL v2"));
    info.SetDescription(
        wxT("Gerador de questões cloze programáveis para o Moodle\nIcon made by Pixel perfect from www.flaticon.com"));
    info.SetName(wxT("Gerador de questões"));
    ::wxAboutBox(info);
}
void MainFrame::OnIntClick(wxCommandEvent& event)
{
}

void MainFrame::SendToConsole(wxString str, wxColour textColour)
{
    int pos = m_richTextCtrlConsole->GetCaretPosition();
    if(str != "") {
        m_richTextCtrlConsole->AppendText(">> " + str + "\n");
        m_richTextCtrlConsole->MoveEnd();
        m_richTextCtrlConsole->ShowPosition(m_richTextCtrlConsole->GetCaretPosition());
    }
    if(textColour != m_dfltConsoleTextColour) {
        wxRichTextRange range(pos + 4, m_richTextCtrlConsole->GetCaretPosition());
        wxRichTextAttr attr;
        m_richTextCtrlConsole->GetStyleForRange(range, attr);
        attr.SetTextColour(textColour);
        attr.SetFontWeight(wxFONTWEIGHT_BOLD);
        m_richTextCtrlConsole->SetStyle(range, attr);
    }
}

PyObject* MainFrame::LoadPyModule(wxCStrData script, std::vector<wxString>& errors)
{
    PyObject* pModule;

    STDCapture captureErrorMsg;
    captureErrorMsg.BeginCapture();

    PyObject* pCompiledFn = Py_CompileString(script, "", Py_file_input);
    pModule = PyImport_ExecCodeModule("strScript", pCompiledFn);

    if(pModule == NULL) {
        PyErr_Print();
        errors.emplace_back(wxT("Falha ao carregar o módulo."));
        captureErrorMsg.EndCapture();
        errors.emplace_back(captureErrorMsg.GetCapture());
        return nullptr;
    } else
        captureErrorMsg.EndCapture();

    return pModule;
}

void MainFrame::RunPythonScript(std::vector<wxString> inputs,
    PyObject* pModule,
    double& returnValue,
    std::vector<wxString>& errors)
{
    PyObject* pFunc;
    PyObject *pArgs, *pValue;

    STDCapture captureErrorMsg;
    captureErrorMsg.BeginCapture();

    if(pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, inputs[0]);
        // pFunc is a new reference

        if(pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(inputs.size() - 1);
            for(unsigned int i = 1; i < inputs.size(); ++i) {
                double dValue = 0.0;
                if(!inputs[i].ToCDouble(&dValue)) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    errors.emplace_back(wxT("Não foi possível converter o argumento."));
                    captureErrorMsg.EndCapture();
                    errors.emplace_back(captureErrorMsg.GetCapture());
                    return;
                }
                pValue = PyFloat_FromDouble(dValue);
                if(!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    errors.emplace_back(wxT("Não foi possível converter o argumento."));
                    captureErrorMsg.EndCapture();
                    errors.emplace_back(captureErrorMsg.GetCapture());
                    return;
                }
                // pValue reference stolen here:
                PyTuple_SetItem(pArgs, i - 1, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if(pValue != NULL) {
                // Retorno com sucesso!! vvv
                returnValue = PyFloat_AsDouble(pValue);
                Py_DECREF(pValue);
            } else {
                Py_DECREF(pFunc);
                PyErr_Print();
                errors.emplace_back(wxT("Não foi possível obter resposta."));
                captureErrorMsg.EndCapture();
                errors.emplace_back(captureErrorMsg.GetCapture());
                return;
            }
        } else {
            if(PyErr_Occurred())
                PyErr_Print();
            errors.emplace_back(wxString::Format(wxT("Função \"%s\" não encontrada."), inputs[0]));
        }
        Py_XDECREF(pFunc);

    } else {
        PyErr_Print();
        errors.emplace_back(wxT("Falha ao carregar o módulo."));
        captureErrorMsg.EndCapture();
        errors.emplace_back(captureErrorMsg.GetCapture());
        return;
    }
    // if(Py_FinalizeEx() < 0) {
    //    captureErrorMsg.EndCapture();
    //    errors.emplace_back(captureErrorMsg.GetCapture());
    //    return;
    //}

    captureErrorMsg.EndCapture();
    errors.emplace_back(captureErrorMsg.GetCapture());
}
void MainFrame::GetInput(wxCommandEvent& event)
{
}
void MainFrame::OnPreviewClick(wxCommandEvent& event)
{

    // auto preview = new HTMLPreview(this, htmlCode);
    // preview->Show();
    // preview->Maximize();
}
void MainFrame::OnIndicatorClick(wxStyledTextEvent& event)
{
    int pos = event.GetPosition();
    IOTag tagClick;
    for(auto tag : m_ioTagList) {
        if(pos >= (tag.position.first + tag.offset) && pos <= (tag.position.second + tag.offset))
            tagClick = tag;
    }
    if(tagClick.name != "") {
        if(tagClick.type == IOTagType::input) {
            SendToConsole(
                wxString::Format(wxT("Entrada: %s\n\tPos = (%d, %d)\n\tInicial = %f, Final = %f, Padrão = %f, CD = %d"),
                    tagClick.name, tagClick.position.first, tagClick.position.second, tagClick.start, tagClick.end,
                    tagClick.stdValue, tagClick.decimalPlaces));
        } else {
            SendToConsole(wxString::Format(wxT("Saída: %s\n\tPos = (%d, %d)\n\tResultado = %f"), tagClick.name,
                tagClick.position.first, tagClick.position.second, tagClick.value));
        }
    }

    for(int i = 0; i < m_gridInputs->GetNumberRows(); ++i) {
        if(tagClick.name == m_gridInputs->GetCellValue(i, 0)) {
            m_gridInputs->SelectRow(i);
            break;
        }
    }

    event.Skip();
}

void MainFrame::FillTable()
{
    m_gridInputs->DeleteRows(0, m_gridInputs->GetNumberRows());

    std::vector<IOTag> newInTagList;
    for(auto& currentTag : m_ioTagList) {
        if(currentTag.type == IOTagType::input) {
            for(auto tableTag : m_ioTagTable) {
                if(currentTag.name == tableTag.name) {
                    currentTag.start = tableTag.start;
                    currentTag.end = tableTag.end;
                    currentTag.stdValue = tableTag.stdValue;
                    currentTag.decimalPlaces = tableTag.decimalPlaces;
                    // SendToConsole(currentTag.name);
                }
            }
            newInTagList.push_back(currentTag);
        }
    }
    m_ioTagTable.clear();
    m_ioTagTable = newInTagList;

    int rowNumber = 0;
    for(auto tag : m_ioTagTable) {
        m_gridInputs->AppendRows(1);
        m_gridInputs->SetCellValue(rowNumber, 0, tag.name);
        m_gridInputs->SetCellValue(rowNumber, 1, wxString::Format("%f", tag.start));
        m_gridInputs->SetCellValue(rowNumber, 2, wxString::Format("%f", tag.end));
        m_gridInputs->SetCellValue(rowNumber, 3, wxString::Format("%f", tag.stdValue));
        m_gridInputs->SetCellValue(rowNumber, 4, wxString::Format("%d", tag.decimalPlaces));
        rowNumber++;
    }
    m_gridInputs->AutoSize();
    m_gridInputs->Layout();
    m_mainPanel->Layout();
}

void MainFrame::OnCellDataChanged(wxGridEvent& event)
{
    // Update table tag list
    for(auto& tag : m_ioTagTable) {
        for(int i = 0; i < m_gridInputs->GetNumberRows(); ++i) {
            if(tag.name == m_gridInputs->GetCellValue(i, 0)) {
                // Get new values
                if(!m_gridInputs->GetCellValue(i, 1).ToDouble(&tag.start))
                    SendToConsole(wxString::Format(wxT("Impossível converter valor da célula (%d, 1)"), i));
                if(!m_gridInputs->GetCellValue(i, 2).ToDouble(&tag.end))
                    SendToConsole(wxString::Format(wxT("Impossível converter valor da célula (%d, 2)"), i));
                if(!m_gridInputs->GetCellValue(i, 3).ToDouble(&tag.stdValue))
                    SendToConsole(wxString::Format(wxT("Impossível converter valor da célula (%d, 3)"), i));
                long int dp = 0;
                if(!m_gridInputs->GetCellValue(i, 4).ToLong(&dp))
                    SendToConsole(wxString::Format(wxT("Impossível converter valor da célula (%d, 4)"), i));
                else
                    tag.decimalPlaces = dp;
            }
        }
    }

    // Update main list
    for(auto& currentTag : m_ioTagList) {
        if(currentTag.type == IOTagType::input) {
            for(auto tableTag : m_ioTagTable) {
                if(currentTag.name == tableTag.name) {
                    currentTag.start = tableTag.start;
                    currentTag.end = tableTag.end;
                    currentTag.stdValue = tableTag.stdValue;
                    currentTag.decimalPlaces = tableTag.decimalPlaces;
                }
            }
        }
    }

    event.Skip();
}

void MainFrame::OnLeftClick(wxGridEvent& event)
{
    m_gridInputs->SetGridCursor(event.GetRow(), event.GetCol());
    // SendToConsole(wxString::Format("(%d, %d)", event.GetRow(), event.GetCol()));
    event.Skip();
}
void MainFrame::OnExportClick(wxCommandEvent& event)
{
    ExportClose expDlg(this);
    if(expDlg.ShowModal() == wxID_OK) {
        ExportXMLToFile(expDlg.m_numQuiz, expDlg.m_catName, expDlg.m_path);
    }

    event.Skip();
}

void MainFrame::ExportXMLToFile(int numQuiz, wxString catName, wxString path)
{
    std::ofstream writeQuizFile(path.mb_str());
    writeQuizFile.close();

    rapidxml::xml_document<> doc;
    rapidxml::file<> xmlFile(path);
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
    rapidxml::xml_attribute<>* ver = doc.allocate_attribute("version", "1.0");
    rapidxml::xml_attribute<>* encoding = doc.allocate_attribute("encoding", "UTF-8");
    decl->append_attribute(ver);
    decl->append_attribute(encoding);
    doc.append_node(decl);

    rapidxml::xml_node<>* rootNode = doc.allocate_node(rapidxml::node_element, "quiz");
    doc.append_node(rootNode);

    rapidxml::xml_node<>* questionCatNode = XMLParser::AppendNode(doc, rootNode, "question");
    XMLParser::SetNodeAttribute(doc, questionCatNode, "type", "category");
    rapidxml::xml_node<>* categoryCatNode = XMLParser::AppendNode(doc, questionCatNode, "category");
    rapidxml::xml_node<>* textCatNode = XMLParser::AppendNode(doc, categoryCatNode, "text");
    XMLParser::SetNodeValue(doc, textCatNode, "$course$/top/" + catName);
    rapidxml::xml_node<>* infoNode = XMLParser::AppendNode(doc, questionCatNode, "info");
    XMLParser::SetNodeAttribute(doc, infoNode, "format", "html");
    rapidxml::xml_node<>* textInfoNode = XMLParser::AppendNode(doc, infoNode, "text");
    rapidxml::xml_node<>* idCatNumberNode = XMLParser::AppendNode(doc, questionCatNode, "idnumber");

    for(int i = 0; i < numQuiz; ++i) {
        rapidxml::xml_node<>* questionClozeNode = XMLParser::AppendNode(doc, rootNode, "question");
        XMLParser::SetNodeAttribute(doc, questionClozeNode, "type", "cloze");
        rapidxml::xml_node<>* nameCloze = XMLParser::AppendNode(doc, questionClozeNode, "name");
        rapidxml::xml_node<>* textCloze = XMLParser::AppendNode(doc, nameCloze, "text");
        XMLParser::SetNodeValue(doc, textCloze, wxString::Format("Q%d", i));
        rapidxml::xml_node<>* questionTextNode = XMLParser::AppendNode(doc, questionClozeNode, "questiontext");
        XMLParser::SetNodeAttribute(doc, questionTextNode, "format", "html");
        rapidxml::xml_node<>* questionTextCloze = XMLParser::AppendNode(doc, questionTextNode, "text");

        // Generate new cloze
        GenerateNewRandomInputValues();
        CalculateOutputs();
        wxString clozeHTLM = "<![CDATA[" + GetHTMLFromCurrentIOs() + "]]>";

        XMLParser::SetNodeValue(doc, questionTextCloze, clozeHTLM.c_str());

        rapidxml::xml_node<>* feedbackNode = XMLParser::AppendNode(doc, questionClozeNode, "generalfeedback");
        XMLParser::SetNodeAttribute(doc, feedbackNode, "format", "html");
        rapidxml::xml_node<>* feedbackTextCloze = XMLParser::AppendNode(doc, feedbackNode, "text");
        rapidxml::xml_node<>* penaltyNode = XMLParser::AppendNode(doc, questionClozeNode, "penalty");
        XMLParser::SetNodeValue(doc, penaltyNode, "0.3333333");
        rapidxml::xml_node<>* hiddenNode = XMLParser::AppendNode(doc, questionClozeNode, "hidden");
        XMLParser::SetNodeValue(doc, hiddenNode, "0");
        rapidxml::xml_node<>* idNumberNode = XMLParser::AppendNode(doc, questionClozeNode, "idnumber");
    }

    std::ofstream writeXML(path.mb_str());
    writeXML << doc;
    writeXML.close();

    // Open the new file and replace escape characters
    wxTextFile xmlFileAgain(path);
    xmlFileAgain.Open();

    wxString fileStr = "";
    for(auto str = xmlFileAgain.GetFirstLine(); !xmlFileAgain.Eof(); str = xmlFileAgain.GetNextLine()) {
        str.Replace("&lt;", "<");
        str.Replace("&gt;", ">");
        str.Replace("&quot;", "\"");
        str.Replace("&apos;", "\'");
        str.Replace("&amp;", "&");
        str.Replace("&nbsp;", " ");

        fileStr += str + "\n";
    }
    // do something with the last line in str
    xmlFileAgain.Clear();
    xmlFileAgain.AddLine(fileStr);
    xmlFileAgain.Write();

    xmlFileAgain.Close();
}

double MainFrame::GetRandom(double init, double end)
{
    std::uniform_real_distribution<> distribution(init, end);
    return distribution(m_rndGenerator);
}

void MainFrame::GenerateNewRandomInputValues()
{
    for(auto& tagTable : m_ioTagTable)
        tagTable.value = GetRandom(tagTable.start, tagTable.end);

    // Update main list
    for(auto& currentTag : m_ioTagList) {
        if(currentTag.type == IOTagType::input) {
            for(auto tableTag : m_ioTagTable) {
                if(currentTag.name == tableTag.name) {
                    currentTag.value = tableTag.value;
                }
            }
        }
    }

    // Set random values
    for(auto& tag : m_ioTagList) {
        tag.value = GetRandom(tag.start, tag.end);
    }
}

bool MainFrame::CalculateOutputs(bool useInputValue)
{
    std::vector<wxString> errors;
    bool noError = true;

    auto* pModule = LoadPyModule(m_stcPython->GetText().c_str(), errors);

    for(auto error : errors) {
        if(error != "") {
            SendToConsole(error);
            noError = false;
        }
    }
    
    if(!noError) return false;

    for(auto& tag : m_ioTagList) {
        if(tag.type == IOTagType::output) {
            wxString str = tag.name;
            wxString partialStr, afterF = "";
            std::vector<wxString> inputs;

            while((partialStr = str.BeforeFirst(' ', &afterF)) != "") {
                inputs.push_back(partialStr);
                str = afterF;
            }

            // Fill inputs with std values
            bool first = true;
            for(auto& in : inputs) {
                if(!first) {
                    for(auto tagTable : m_ioTagTable) {
                        if(in == tagTable.name) {
                            if(useInputValue)
                                in = wxString::FromCDouble(tagTable.value);
                            else
                                in = wxString::FromCDouble(tagTable.stdValue);
                            // SendToConsole(wxString::FromCDouble(GetRandom(tagTable.start, tagTable.end),
                            // tagTable.decimalPlaces));
                        }
                    }
                } else {
                    first = false;
                }
            }

            double response = 0.0;
            RunPythonScript(inputs, pModule, response, errors);

            for(auto error : errors) {
                if(error != "") {
                    SendToConsole(error);
                    noError = false;
                }
            }
            // SendToConsole(inputs[0] + " = " + wxString::FromCDouble(response));
            tag.value = response;
        }
    }
    if(pModule != NULL)
        Py_DECREF(pModule);

    return noError;
}

wxString MainFrame::GetHTMLFromCurrentIOs()
{
    wxString htmlCode = m_stcHTML->GetValue();

    // Set inputs and outputs in html
    for(auto tag : m_ioTagList) {
        wxString ioStr = tag.type == IOTagType::input ? "+" : "-";
        wxString strToReplace = "[[" + ioStr + tag.name + "]]";
        if(tag.type == IOTagType::input)
            htmlCode.Replace(strToReplace, wxString::FromCDouble(tag.value, tag.decimalPlaces));
        else
            htmlCode.Replace(strToReplace, wxString::FromCDouble(tag.value));
    }
    htmlCode.Replace("\n", "");

    return htmlCode;
}
void MainFrame::OnOpenClick(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(
        this, wxT("Abrir arquivo ANTHA"), "", "", "Arquivo ANTHA (*.antha)|*.antha", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxTextFile file(openFileDialog.GetPath());
    OpenFile(file);
    FormatHTML();
}
void MainFrame::OnSaveAsClick(wxCommandEvent& event)
{

    wxFileDialog saveFileDialog(this, wxT("Salvar arquivo ANTHA"), "", "", "Arquivo ANTHA (*.antha)|*.antha",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    m_filePath = saveFileDialog.GetPath();

    wxString saveStr = GetStrSave();

    wxTextFile file(m_filePath);
    file.AddLine(saveStr);
    file.Write();
    file.Close();
}

void MainFrame::OnSaveClick(wxCommandEvent& event)
{
    if(m_filePath == "") {
        wxFileDialog saveFileDialog(this, wxT("Salvar arquivo ANTHA"), "", "", "Arquivo ANTHA (*.antha)|*.antha",
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if(saveFileDialog.ShowModal() == wxID_CANCEL)
            return;
        m_filePath = saveFileDialog.GetPath();
    }

    wxString saveStr = GetStrSave();

    wxTextFile file(m_filePath);
    file.AddLine(saveStr);
    file.Write();
    file.Close();
}

wxString MainFrame::GetStrSave()
{
    wxString strSave = "";
    strSave += "init html\n" + m_stcHTML->GetValue() + "\nend html\n";
    strSave += "init py\n" + m_stcPython->GetValue() + "\nend py\n";
    strSave += "init io\n";
    for(auto tag : m_ioTagList) {
        strSave += wxString::Format("%d;", tag.type);
        strSave += tag.name + ";";
        strSave += wxString::FromCDouble(tag.start) + ";";
        strSave += wxString::FromCDouble(tag.end) + ";";
        strSave += wxString::FromCDouble(tag.stdValue) + ";";
        strSave += wxString::Format("%d;", tag.decimalPlaces);
        strSave += wxString::Format("%d;%d;\n", tag.position.first, tag.position.second);
    }
    strSave += "end io\n";

    return strSave;
}

void MainFrame::OpenFile(wxTextFile& file)
{
    file.Open();

    m_ioTagList.clear();
    m_ioTagTable.clear();

    wxString htmlStr = "";
    wxString pyStr = "";
    for(auto str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine()) {
        if(str == "init html") {
            str = file.GetNextLine();
            while(str != "end html") {
                htmlStr += str + "\n";
                str = file.GetNextLine();
            }
            htmlStr.Remove(htmlStr.size() - 1);
        }
        if(str == "init py") {
            str = file.GetNextLine();
            while(str != "end py") {
                pyStr += str + "\n";
                str = file.GetNextLine();
            }
            pyStr.Remove(pyStr.size() - 1);
        }
        if(str == "init io") {
            str = file.GetNextLine();
            while(str != "end io") {
                std::vector<wxString> ioStrs;
                wxString ioValueStr = "";
                for(auto ch : str) {
                    if(ch == ';') {
                        ioStrs.push_back(ioValueStr);
                        ioValueStr = "";
                    } else {
                        ioValueStr += ch;
                    }
                }
                IOTag newTag;

                long typeID, decimalPlaces, startPos, endPos;
                double start, end, stdValue;

                ioStrs[0].ToLong(&typeID);
                ioStrs[2].ToDouble(&start);
                ioStrs[3].ToDouble(&end);
                ioStrs[4].ToDouble(&stdValue);
                ioStrs[5].ToLong(&decimalPlaces);
                ioStrs[6].ToLong(&startPos);
                ioStrs[7].ToLong(&endPos);

                newTag.type = static_cast<IOTagType>(typeID);
                newTag.name = ioStrs[1];
                newTag.start = start;
                newTag.end = end;
                newTag.stdValue = stdValue;
                newTag.decimalPlaces = decimalPlaces;
                newTag.position = std::make_pair<int>(startPos, endPos);

                m_ioTagList.push_back(newTag);

                str = file.GetNextLine();
            }
        }
    }
    // do something with the last line in str

    m_stcHTML->ClearAll();
    m_stcHTML->SetValue(htmlStr);

    m_stcPython->ClearAll();
    m_stcPython->SetValue(pyStr);

    FillTable();

    m_filePath = file.GetName();

    file.Close();
}
void MainFrame::OnMarginClick(wxStyledTextEvent& event)
{
    m_stcHTML->ToggleFold(m_stcHTML->LineFromPosition(event.GetPosition()));
}

void MainFrame::FormatHTML()
{
    wxString newHTMLTxt = "";
    for(int i = 0; i < m_stcHTML->GetNumberOfLines(); ++i) {
        wxString line = m_stcHTML->GetLine(i);
        wxString token = "img src=";
        int tokenPos = line.Find(token);
        if(tokenPos != wxNOT_FOUND) {
            if(tokenPos + token.size() < line.size()) {
                if(line[tokenPos + token.size()] != '\n') {
                    line.insert(tokenPos + token.size(), "\n");
                    int lastTokenPos = line.Find('"', true);
                    if(lastTokenPos != wxNOT_FOUND) {
                        line.insert(lastTokenPos + 1, "\n");
                    }
                }
            }
        }
        newHTMLTxt += line;
    }
    m_stcHTML->SetValue(newHTMLTxt);
    std::vector<int> linesWithImg;
    for(int i = 0; i < m_stcHTML->GetNumberOfLines(); ++i) {
        wxString line = m_stcHTML->GetLine(i);
        if(line.Find("img src=") != wxNOT_FOUND) {
            m_stcHTML->SetFoldLevel(i, 1024 | wxSTC_FOLDLEVELHEADERFLAG);
            m_stcHTML->SetFoldLevel(++i, 1025);
        }
    }
    m_stcHTML->FoldAll(0);
}
void MainFrame::OAboutRibbonClick(wxRibbonButtonBarEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.AddDeveloper(wxT("Thales Lima Oliveira"));
    info.SetLicence(wxT("GPL v2"));
    info.SetDescription(
        wxT("Gerador de questões cloze programáveis para o Moodle\nIcon made by Pixel perfect from www.flaticon.com"));
    info.SetName(wxT("Gerador de questões"));
    ::wxAboutBox(info);
}
void MainFrame::OnExportRibbonClick(wxRibbonButtonBarEvent& event)
{
    ExportClose expDlg(this);
    if(expDlg.ShowModal() == wxID_OK) {
        ExportXMLToFile(expDlg.m_numQuiz, expDlg.m_catName, expDlg.m_path);
    }
}
void MainFrame::OnGetInputRibbonClick(wxRibbonButtonBarEvent& event)
{
    FormatHTML();
    m_ioTagList.clear(); // Cleaning all previous tags

    int pos = 0;
    m_numNonASCIICh = 0;
    std::vector<int> currentNumNonASCIICh;
    std::vector<int> startPos;
    std::vector<int> endPos;
    bool prevSBrackets = false;
    bool prevEBrackets = false;
    for(auto ch : m_stcHTML->GetValue()) {
        if(ch == '[') {
            if(prevSBrackets) {
                startPos.push_back(pos + 1);
                currentNumNonASCIICh.push_back(m_numNonASCIICh);
            } else
                prevSBrackets = true;
        } else {
            prevSBrackets = false;
        }

        if(ch == ']') {
            if(prevEBrackets) {
                endPos.push_back(pos - 1);
            } else
                prevEBrackets = true;
        } else {
            prevEBrackets = false;
        }

        pos++;

        if(static_cast<unsigned char>(ch) > 127)
            m_numNonASCIICh++;
    }
    if(startPos.size() != endPos.size()) {
        SendToConsole(wxT("Erro ao analisar os colchetes ('[[' e ']]') de entradas e saídas, verifique as tags "
                          "inseridas no arquivo HTML"));
        return;
    }

    for(unsigned int i = 0; i < startPos.size(); ++i) {
        wxString tagStr = m_stcHTML->GetValue().Mid(startPos[i], endPos[i] - startPos[i]);
        IOTag newIOTag;
        if(tagStr[0] == '+')
            newIOTag.type = IOTagType::input;
        else if(tagStr[0] == '-')
            newIOTag.type = IOTagType::output;
        else {
            SendToConsole(wxT("Erro ao analisar as tags ('+' e '-') de entradas e saídas, verifique o arquivo HTML"));
            return;
        }
        newIOTag.name = tagStr.Right(tagStr.Length() - 1);
        newIOTag.position = std::make_pair(startPos[i], endPos[i]);
        newIOTag.offset = currentNumNonASCIICh[i];

        m_ioTagList.push_back(newIOTag);
    }

    m_stcHTML->IndicatorClearRange(0, m_stcHTML->GetValue().length());
    for(auto tag : m_ioTagList) {
        m_stcHTML->IndicatorFillRange(tag.position.first + tag.offset, tag.position.second - tag.position.first);
    }

    FillTable();
}
void MainFrame::OnOpenRibbonClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog openFileDialog(
        this, wxT("Abrir arquivo ANTHA"), "", "", "Arquivo ANTHA (*.antha)|*.antha", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxTextFile file(openFileDialog.GetPath());
    OpenFile(file);
    FormatHTML();
}
void MainFrame::OnPreviewRibbonClick(wxRibbonButtonBarEvent& event)
{
    wxString htmlCode = m_stcHTML->GetValue();

    // Set inputs and outputs in html
    for(auto tag : m_ioTagList) {
        wxString ioStr = tag.type == IOTagType::input ? "+" : "-";
        wxString strToReplace = "[[" + ioStr + tag.name + "]]";
        if(tag.type == IOTagType::input) {
            htmlCode.Replace(strToReplace, wxString::FromDouble(tag.stdValue));
        } else {
            htmlCode.Replace(strToReplace, wxString::FromDouble(tag.value));
        }
    }

    m_webViewPreview->SetPage("<html><body>" + htmlCode + "</html></body>", "");

    m_notebookMain->SetSelection(1);
}
void MainFrame::OnQuitRibbonClick(wxRibbonButtonBarEvent& event)
{
    Close();
}
void MainFrame::OnRunPyRibbonClick(wxRibbonButtonBarEvent& event)
{
    if(CalculateOutputs(false)) {
        SendToConsole(wxT("Script interpretado com sucesso! Clique em 'Preview' para visualizar as respostas padrões."),
            *wxGREEN);
    } else {
        SendToConsole(wxT("Script com erro(s). Não foi possível calcular todas as saídas."), wxColour(252, 143, 0));
    }
}
void MainFrame::OnSaveAsRibbonClick(wxRibbonButtonBarEvent& event)
{
    wxFileDialog saveFileDialog(this, wxT("Salvar arquivo ANTHA"), "", "", "Arquivo ANTHA (*.antha)|*.antha",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    m_filePath = saveFileDialog.GetPath();

    wxString saveStr = GetStrSave();

    wxTextFile file(m_filePath);
    file.AddLine(saveStr);
    file.Write();
    file.Close();
}
void MainFrame::OnSaveRibbonClick(wxRibbonButtonBarEvent& event)
{
    if(m_filePath == "") {
        wxFileDialog saveFileDialog(this, wxT("Salvar arquivo ANTHA"), "", "", "Arquivo ANTHA (*.antha)|*.antha",
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if(saveFileDialog.ShowModal() == wxID_CANCEL)
            return;
        m_filePath = saveFileDialog.GetPath();
    }

    wxString saveStr = GetStrSave();

    wxTextFile file(m_filePath);
    file.AddLine(saveStr);
    file.Write();
    file.Close();
}
void MainFrame::OnWindowClose(wxCloseEvent& event)
{
    wxMessageDialog dlg(
        this, wxT("Deseja realmente sair sem salvar?"), wxT("Atenção!"), wxYES_NO | wxICON_WARNING | wxCENTRE);
    if(dlg.ShowModal() != wxID_NO)
        event.Skip();
}
void MainFrame::OnNewClick(wxCommandEvent& event)
{
}
