#include "MainFrame.h"
#include "STDCapture.h"
#include <sstream>
#include <vector>
#include <wx/aboutdlg.h>
#include <wx/ffile.h>
#include <wx/fs_mem.h>
#include <wx/msgdlg.h>
#include <wx/sharedptr.h>
#include <wx/stdpaths.h>
#include <wx/webviewfshandler.h>

#include "ExportClose.h"
#include "HTMLPreview.h"
#include "XMLParser.h"

// namespace py = pybind11;
// using namespace py::literals;

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    SetTitle(wxT("Gerador de questões"));
    SetSize(GetBestSize());

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
    m_stcHTML->SetLexer(wxSTC_LEX_PYTHON);

    m_stcHTML->SetText("<!-- Cole o HTML do Moodle aqui! -->\n[[+t1]] + [[+t2]] = [[-soma t1 t2]]");

    m_stcHTML->StyleSetForeground(wxSTC_H_ATTRIBUTE, wxColour(150, 0, 0));
    m_stcHTML->StyleSetForeground(wxSTC_H_DOUBLESTRING, wxColour(40, 0, 60));
    m_stcHTML->StyleSetForeground(wxSTC_H_NUMBER, wxColour(0, 150, 0));
    m_stcHTML->StyleSetForeground(wxSTC_H_TAG, wxColour(150, 0, 0));
    m_stcHTML->StyleSetForeground(wxSTC_H_TAGEND, wxColour(150, 0, 150));
    m_stcHTML->StyleSetForeground(wxSTC_H_ENTITY, wxColour(0, 0, 150));
    m_stcHTML->StyleSetForeground(wxSTC_H_ASP, wxColour(255, 165, 0));
    m_stcHTML->StyleSetForeground(wxSTC_H_COMMENT, wxColour(150, 150, 150));

    // highlight indicator
    m_stcHTML->IndicatorSetStyle(m_highlightID, wxSTC_INDIC_ROUNDBOX);
    m_stcHTML->IndicatorSetHoverStyle(m_highlightID, wxSTC_INDIC_ROUNDBOX);
    m_stcHTML->IndicatorSetAlpha(m_highlightID, 200);
    m_stcHTML->IndicatorSetUnder(m_highlightID, true);
    m_stcHTML->IndicatorSetForeground(m_highlightID, wxColor(255, 0, 0));
    m_stcHTML->SetIndicatorCurrent(m_highlightID);

    auto style = m_richTextCtrlConsole->GetBasicStyle();
    style.SetTextColour(*wxWHITE);
    m_richTextCtrlConsole->SetBasicStyle(style);

    m_gridInputs->SetDefaultColSize(200);
    m_gridInputs->SetDefaultCellFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    m_gridInputs->SetLabelFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
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
}

MainFrame::~MainFrame()
{
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
    info.SetDescription(wxT("Gerador de questões cloze programáveis para o Moodle"));
    info.SetName(wxT("Gerador de questões"));
    ::wxAboutBox(info);
}
void MainFrame::OnIntClick(wxCommandEvent& event)
{
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
                            in = wxString::FromCDouble(tagTable.stdValue);
                        }
                    }
                } else {
                    first = false;
                }
            }

            std::vector<wxString> errors;
            double response = 0.0;
            RunPythonScript(inputs, m_stcPython->GetText().c_str(), response, errors);

            for(auto error : errors)
                SendToConsole(error);

            SendToConsole(inputs[0] + " = " + wxString::FromCDouble(response));
            tag.result = response;
        }
    }
}

void MainFrame::SendToConsole(wxString str)
{
    if(str != "") {
        m_richTextCtrlConsole->AppendText(">> " + str + "\n");
        m_richTextCtrlConsole->MoveEnd();
        m_richTextCtrlConsole->ShowPosition(m_richTextCtrlConsole->GetCaretPosition());
    }
}

void MainFrame::RunPythonScript(std::vector<wxString> inputs,
    wxCStrData script,
    double& returnValue,
    std::vector<wxString>& errors)
{
    PyObject *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    STDCapture captureErrorMsg;
    captureErrorMsg.BeginCapture();

    Py_Initialize();

    PyObject* pCompiledFn = Py_CompileString(script, "", Py_file_input);
    pModule = PyImport_ExecCodeModule("strScript", pCompiledFn);

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
                Py_DECREF(pModule);
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
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
        errors.emplace_back(wxT("Falha ao carregar o módulo."));
        captureErrorMsg.EndCapture();
        errors.emplace_back(captureErrorMsg.GetCapture());
        return;
    }
    if(Py_FinalizeEx() < 0) {
        captureErrorMsg.EndCapture();
        errors.emplace_back(captureErrorMsg.GetCapture());
        return;
    }

    captureErrorMsg.EndCapture();
    errors.emplace_back(captureErrorMsg.GetCapture());
}
void MainFrame::GetInput(wxCommandEvent& event)
{
    m_ioTagList.clear(); // Cleaning all previous tags

    int pos = 0;
    std::vector<int> startPos;
    std::vector<int> endPos;
    bool prevSBrackets, prevEBrackets = false;
    for(auto ch : m_stcHTML->GetValue()) {
        if(ch == '[') {
            if(prevSBrackets) {
                startPos.push_back(pos + 1);
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

        m_ioTagList.push_back(newIOTag);
    }

    for(auto tag : m_ioTagList) {
        m_stcHTML->IndicatorFillRange(tag.position.first, tag.position.second - tag.position.first);
    }

    FillTable();
}
void MainFrame::OnPreviewClick(wxCommandEvent& event)
{
    wxString htmlCode = m_stcHTML->GetValue();

    // Set inputs and outputs in html
    for(auto tag : m_ioTagList) {
        wxString ioStr = tag.type == IOTagType::input ? "+" : "-";
        wxString strToReplace = "[[" + ioStr + tag.name + "]]";
        if(tag.type == IOTagType::input) {
            htmlCode.Replace(strToReplace, wxString::FromDouble(tag.stdValue));
        } else {
            htmlCode.Replace(strToReplace, wxString::FromDouble(tag.result));
        }
    }

    auto preview = new HTMLPreview(this, htmlCode);
    preview->Show();
    preview->Maximize();
}
void MainFrame::OnIndicatorClick(wxStyledTextEvent& event)
{
    int pos = event.GetPosition();
    IOTag tagClick;
    for(auto tag : m_ioTagList) {
        if(pos >= tag.position.first && pos <= tag.position.second)
            tagClick = tag;
    }
    SendToConsole(
        wxString::Format("%s, %s, pos = (%d, %d), init = %f, end = %f, std = %f, dp = %d, res = %f", tagClick.name,
            tagClick.type == IOTagType::input ? "in" : "out", tagClick.position.first, tagClick.position.second,
            tagClick.start, tagClick.end, tagClick.stdValue, tagClick.decimalPlaces, tagClick.result));

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
        ExportXMLToFile(expDlg.m_numQuiz, expDlg.m_catName, expDlg.m_path, expDlg.m_filename);
    }

    event.Skip();
}

void MainFrame::ExportXMLToFile(int numQuiz, wxString catName, wxString path, wxString filename)
{
    std::ofstream writeQuizFile(path.mb_str());
    writeQuizFile.close();

    rapidxml::xml_document<> doc;
    rapidxml::file<> xmlFile(path);
    doc.parse<0>(xmlFile.data());
    
    rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
    rapidxml::xml_attribute<>* ver = doc.allocate_attribute("version", "1.0");
    rapidxml::xml_attribute<>* encoding = doc.allocate_attribute("encoding", "utf-8");
    decl->append_attribute(ver);
    decl->append_attribute(encoding);
    doc.append_node(decl);
    
    rapidxml::xml_node<>* rootNode = doc.allocate_node(rapidxml::node_element, "quiz");
    doc.append_node(rootNode);

    rapidxml::xml_node<>* processNameNode = XMLParser::AppendNode(doc, rootNode, "question");
    XMLParser::SetNodeAttribute(doc, processNameNode, "type", "category");
    //XMLParser::SetNodeValue(doc, processNameNode, fileName);
}
