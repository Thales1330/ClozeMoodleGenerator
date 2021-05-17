#include "MainFrame.h"
//#include "wx/msw/webview_ie.h" // not working
#include <random>
#include <sstream>
#include <vector>
#include <wx/aboutdlg.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/tokenzr.h>

#include "ExportClose.h"
#include "XMLParser.h"

namespace emb
{
// Copyright (C) 2011 Mateusz Loskot <mateusz@loskot.net>
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Blog article: http://mateusz.loskot.net/?p=2819

typedef std::function<void(std::string)> stderr_write_type;
typedef std::function<void(std::string)> stdout_write_type;

struct Stderr {
    PyObject_HEAD stderr_write_type write;
};

struct Stdout {
    PyObject_HEAD stdout_write_type write;
};

PyObject* Stderr_write(PyObject* self, PyObject* args)
{
    std::size_t written(0);
    Stderr* selfimpl = reinterpret_cast<Stderr*>(self);
    if(selfimpl->write) {
        char* data;
        if(!PyArg_ParseTuple(args, "s", &data))
            return 0;

        std::string str(data);
        selfimpl->write(str);
        written = str.size();
    }
    return PyLong_FromSize_t(written);
}

PyObject* Stdout_write(PyObject* self, PyObject* args)
{
    std::size_t written(0);
    Stdout* selfimpl = reinterpret_cast<Stdout*>(self);
    if (selfimpl->write) {
        char* data;
        if (!PyArg_ParseTuple(args, "s", &data))
            return 0;

        std::string str(data);
        selfimpl->write(str);
        written = str.size();
    }
    return PyLong_FromSize_t(written);
}

PyObject* Stderr_flush(PyObject* self, PyObject* args)
{
    // no-op
    return Py_BuildValue("");
}

PyObject* Stdout_flush(PyObject* self, PyObject* args)
{
    // no-op
    return Py_BuildValue("");
}

PyMethodDef Stderr_methods[] = {
    { "write", Stderr_write, METH_VARARGS, "sys.stderr.write" },
    { "flush", Stderr_flush, METH_VARARGS, "sys.stderr.flush" }, { 0, 0, 0, 0 } // sentinel
};

PyMethodDef Stdout_methods[] = {
{ "write", Stdout_write, METH_VARARGS, "sys.stdout.write" },
{ "flush", Stdout_flush, METH_VARARGS, "sys.stdout.flush" }, { 0, 0, 0, 0 } // sentinel
};

PyTypeObject StderrType = {
    PyVarObject_HEAD_INIT(0, 0) "emb.StderrType", /* tp_name */
    sizeof(Stderr),                               /* tp_basicsize */
    0,                                            /* tp_itemsize */
    0,                                            /* tp_dealloc */
    0,                                            /* tp_print */
    0,                                            /* tp_getattr */
    0,                                            /* tp_setattr */
    0,                                            /* tp_reserved */
    0,                                            /* tp_repr */
    0,                                            /* tp_as_number */
    0,                                            /* tp_as_sequence */
    0,                                            /* tp_as_mapping */
    0,                                            /* tp_hash  */
    0,                                            /* tp_call */
    0,                                            /* tp_str */
    0,                                            /* tp_getattro */
    0,                                            /* tp_setattro */
    0,                                            /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                           /* tp_flags */
    "emb.Stderr objects",                         /* tp_doc */
    0,                                            /* tp_traverse */
    0,                                            /* tp_clear */
    0,                                            /* tp_richcompare */
    0,                                            /* tp_weaklistoffset */
    0,                                            /* tp_iter */
    0,                                            /* tp_iternext */
    Stderr_methods,                               /* tp_methods */
    0,                                            /* tp_members */
    0,                                            /* tp_getset */
    0,                                            /* tp_base */
    0,                                            /* tp_dict */
    0,                                            /* tp_descr_get */
    0,                                            /* tp_descr_set */
    0,                                            /* tp_dictoffset */
    0,                                            /* tp_init */
    0,                                            /* tp_alloc */
    0,                                            /* tp_new */
};

PyTypeObject StdoutType = {
PyVarObject_HEAD_INIT(0, 0) "emb.StdoutType", /* tp_name */
sizeof(Stdout),                               /* tp_basicsize */
0,                                            /* tp_itemsize */
0,                                            /* tp_dealloc */
0,                                            /* tp_print */
0,                                            /* tp_getattr */
0,                                            /* tp_setattr */
0,                                            /* tp_reserved */
0,                                            /* tp_repr */
0,                                            /* tp_as_number */
0,                                            /* tp_as_sequence */
0,                                            /* tp_as_mapping */
0,                                            /* tp_hash  */
0,                                            /* tp_call */
0,                                            /* tp_str */
0,                                            /* tp_getattro */
0,                                            /* tp_setattro */
0,                                            /* tp_as_buffer */
Py_TPFLAGS_DEFAULT,                           /* tp_flags */
"emb.Stdout objects",                         /* tp_doc */
0,                                            /* tp_traverse */
0,                                            /* tp_clear */
0,                                            /* tp_richcompare */
0,                                            /* tp_weaklistoffset */
0,                                            /* tp_iter */
0,                                            /* tp_iternext */
Stdout_methods,                               /* tp_methods */
0,                                            /* tp_members */
0,                                            /* tp_getset */
0,                                            /* tp_base */
0,                                            /* tp_dict */
0,                                            /* tp_descr_get */
0,                                            /* tp_descr_set */
0,                                            /* tp_dictoffset */
0,                                            /* tp_init */
0,                                            /* tp_alloc */
0,                                            /* tp_new */
};

PyModuleDef embmodule = {
    PyModuleDef_HEAD_INIT,
    "emb",
    0,
    -1,
    0,
};

// Internal state
PyObject* g_stderr;
PyObject* g_stderr_saved;

PyObject* g_stdout;
PyObject* g_stdout_saved;

PyMODINIT_FUNC PyInit_emb(void)
{
    g_stderr = 0;
    g_stdout = 0;
    g_stderr_saved = 0;
    g_stdout_saved = 0;

    StderrType.tp_new = PyType_GenericNew;
    if(PyType_Ready(&StderrType) < 0)
        return 0;

    StdoutType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&StdoutType) < 0)
        return 0;

    PyObject* m = PyModule_Create(&embmodule);
    if(m) {
        Py_INCREF(&StderrType);
        PyModule_AddObject(m, "Stderr", reinterpret_cast<PyObject*>(&StderrType));
        PyModule_AddObject(m, "Stdout", reinterpret_cast<PyObject*>(&StdoutType));
    }
    return m;
}

void set_stderr(stderr_write_type write)
{
    if(!g_stderr) {
        g_stderr_saved = PySys_GetObject("stderr"); // borrowed
        g_stderr = StderrType.tp_new(&StderrType, 0, 0);
    }

    Stderr* impl = reinterpret_cast<Stderr*>(g_stderr);
    impl->write = write;
    PySys_SetObject("stderr", g_stderr);
}

void set_stdout(stdout_write_type write)
{
    if (!g_stdout) {
        g_stdout_saved = PySys_GetObject("stdout"); // borrowed
        g_stdout = StdoutType.tp_new(&StdoutType, 0, 0);
    }

    Stdout* impl = reinterpret_cast<Stdout*>(g_stdout);
    impl->write = write;
    PySys_SetObject("stdout", g_stdout);
}

void reset_stderr()
{
    if(g_stderr_saved)
        PySys_SetObject("stderr", g_stderr_saved);

    Py_XDECREF(g_stderr);
    g_stderr = 0;
}

void reset_stdout()
{
    if (g_stdout_saved)
        PySys_SetObject("stdout", g_stdout_saved);

    Py_XDECREF(g_stdout);
    g_stdout = 0;
}

} // namespace emb

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    m_rndGenerator.seed(time(0));
    SetTitle(wxT("Gerador de questões"));
    SetSize(GetBestSize());

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
    m_gridInputs->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
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

    PyImport_AppendInittab("emb", emb::PyInit_emb);
    Py_Initialize();
    PyImport_ImportModule("emb");

    SaveIsNeeded(false);
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
    ShowAbout();
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

PyObject* MainFrame::LoadPyModule(const wxString &script, std::vector<wxString>& errors)
{
    PyObject* pModule;

    PyObject* pCompiledFn = Py_CompileString(script.ToUTF8(), "", Py_file_input);
    pModule = PyImport_ExecCodeModule("strScript", pCompiledFn);

    if(pModule == nullptr) {
        std::string buffer;
        {
            emb::stderr_write_type write = [&buffer](std::string s) { buffer += s; };
            emb::set_stderr(write);
            PyErr_Print();
            emb::reset_stderr();
            errors.emplace_back(wxT("Falha ao carregar o módulo."));
        }
        errors.emplace_back(buffer);
        return nullptr;
    }

    return pModule;
}

void MainFrame::RunPythonScript(std::vector<wxString> inputs,
    PyObject* pModule,
    IOTag& tag,
    std::vector<wxString>& errors)
{
    PyObject* pFunc;
    PyObject *pArgs, *pValue;

    if(inputs[0] != "double" && inputs[0] != "str" && inputs[0] != "int")
    {
        inputs.emplace(inputs.begin(), "double");
    }

    std::string buffer;
    {
        emb::stderr_write_type write = [&buffer](std::string s) { buffer += s; };
        emb::set_stderr(write);

        if(pModule != nullptr) {
            pFunc = PyObject_GetAttrString(pModule, inputs[1]);
            // pFunc is a new reference

            if(pFunc && PyCallable_Check(pFunc)) {
                pArgs = PyTuple_New(inputs.size() - 2);
                for(unsigned int i = 2; i < inputs.size(); ++i) {
                    bool conversionError = false;
                    double dValue = 0.0;
                    conversionError = !inputs[i].ToCDouble(&dValue);

                    pValue = PyFloat_FromDouble(dValue);

                    if (conversionError) {
                        Py_DECREF(pArgs);
                        errors.emplace_back(wxT("Não foi possível converter o argumento."));
                        errors.emplace_back(wxString::Format(
                            wxT("Não foi possível converter o argumento da função \"%s\""), inputs[1]));
                        errors.emplace_back(buffer);
                        return;
                    }

                    if (!pValue) {
                        Py_DECREF(pArgs);
                        errors.emplace_back(wxString::Format(
                            wxT("Não foi possível converter o argumento da função \"%s\""), inputs[1]));
                        errors.emplace_back(buffer);
                        return;
                    }

                    // pValue reference stolen here:
                    PyTuple_SetItem(pArgs, i - 2, pValue);
                }

                // Run py function
                std::string bufferOut;
                {
                    emb::stdout_write_type writeOut = [&bufferOut](std::string s2) { bufferOut += s2; };
                    emb::set_stdout(writeOut);

                    pValue = PyObject_CallObject(pFunc, pArgs);

                    emb::reset_stdout();
                    if(!bufferOut.empty())
                        SendToConsole(wxString::Format(wxT("Mensagens da função %s:\n%s"), inputs[1], bufferOut));
                    Py_DECREF(pArgs);
                }


                if(pValue != nullptr) {
                    tag.valueType = inputs[0];

                    if (inputs[0] == "double") {
                        tag.value = PyFloat_AsDouble(pValue);
                    } else if(inputs[0] == "int")
                    {
                        tag.valueInt = PyLong_AsLong(pValue);
                    } else if (inputs[0] == "str")
                    {
                        tag.valueStr = PyUnicode_AsUTF8(pValue);
                    }

                    Py_DECREF(pValue);
                } else {
                    Py_DECREF(pFunc);
                    PyErr_Print();
                    emb::reset_stderr();
                    errors.emplace_back(
                        wxString::Format(wxT("Não foi possível obter resposta da função \"%s\""), inputs[1]));
                    errors.emplace_back(buffer);
                    return;
                }
            } else {
                if(PyErr_Occurred()) {
                    PyErr_Print();
                }
                emb::reset_stderr();
                errors.emplace_back(wxString::Format(wxT("Função \"%s\" não encontrada."), inputs[1]));
                errors.emplace_back(buffer);
            }
            Py_XDECREF(pFunc);

        } else {
            PyErr_Print();
            emb::reset_stderr();
            errors.emplace_back(wxT("Falha ao carregar o módulo."));
            errors.emplace_back(buffer);
            return;
        }
        emb::reset_stderr();
    }

    errors.emplace_back(buffer);
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
        }
        else if (tagClick.type == IOTagType::output) {
            if (tagClick.valueType == "double") {
                SendToConsole(wxString::Format(wxT("Saída: %s\n\tPos = (%d, %d)\n\tResultado (double) = %f"), tagClick.name,
                    tagClick.position.first, tagClick.position.second, tagClick.value));
            }
            else if (tagClick.valueType == "int") {
                SendToConsole(wxString::Format(wxT("Saída: %s\n\tPos = (%d, %d)\n\tResultado (int) = %d"), tagClick.name,
                    tagClick.position.first, tagClick.position.second, tagClick.valueInt));
            }
            else if (tagClick.valueType == "str") {
                SendToConsole(wxString::Format(wxT("Saída: %s\n\tPos = (%d, %d)\n\tResultado (str) = %s"), tagClick.name,
                    tagClick.position.first, tagClick.position.second, tagClick.valueStr));
            }
        }
        else if (tagClick.type == IOTagType::equal) {
            SendToConsole(
                wxString::Format(wxT("Igual: %s\n\tPos = (%d, %d)\n\tPadrão = %f, CD = %d"),
                    tagClick.name, tagClick.position.first, tagClick.position.second,
                    tagClick.stdValue, tagClick.decimalPlaces));
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

    // If the new input (or equal) have the same name as old table list, inherit the old parameters
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
        else if (currentTag.type == IOTagType::equal) {
            for (const auto& tableTag : m_ioTagTable)
            {
                // Same name as input type
                if (currentTag.name == tableTag.name)
                {
                    currentTag.value = tableTag.value;
                    currentTag.stdValue = tableTag.stdValue;
                    currentTag.decimalPlaces = tableTag.decimalPlaces;
                }
            }
        }
    }
    m_ioTagTable.clear();
    m_ioTagTable = newInTagList;

    int rowNumber = 0;
    for(auto tag : m_ioTagTable) {
        m_gridInputs->AppendRows(1);
        m_gridInputs->SetCellValue(rowNumber, 0, tag.name);
        m_gridInputs->SetCellValue(rowNumber, 1, wxString::FromDouble(tag.start, tag.decimalPlaces));
        m_gridInputs->SetCellValue(rowNumber, 2, wxString::FromDouble(tag.end, tag.decimalPlaces));
        m_gridInputs->SetCellValue(rowNumber, 3, wxString::FromDouble(tag.stdValue, tag.decimalPlaces));
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
                    SendToConsole(wxString::Format(wxT("Impossível converter valor \"%s\" da célula (%d, 2) na coluna \"Inicial\"."), m_gridInputs->GetCellValue(i, 1), i + 1), wxColour(255, 255, 0));
                if(!m_gridInputs->GetCellValue(i, 2).ToDouble(&tag.end))
                    SendToConsole(wxString::Format(wxT("Impossível converter valor \"%s\" da célula (%d, 3) na coluna \"Final\"."), m_gridInputs->GetCellValue(i, 2), i + 1), wxColour(255, 255, 0));
                if(!m_gridInputs->GetCellValue(i, 3).ToDouble(&tag.stdValue))
                    SendToConsole(wxString::Format(wxT("Impossível converter valor \"%s\" da célula (%d, 4) na coluna \"Padrão\"."), m_gridInputs->GetCellValue(i, 3), i + 1), wxColour(255, 255, 0));
                long int dp = 0;
                if(!m_gridInputs->GetCellValue(i, 4).ToLong(&dp))
                    SendToConsole(wxString::Format(wxT("Impossível converter valor \"%s\" da célula (%d, 5) na coluna \"Casas decimais\"."), m_gridInputs->GetCellValue(i, 4), i + 1), wxColour(255, 255, 0));
                else
                    tag.decimalPlaces = dp;
            }
        }
    }

    // Update main list
    for(auto& currentTag : m_ioTagList) {
        if(currentTag.type == IOTagType::input) {
            for(const auto& tableTag : m_ioTagTable) {
                if(currentTag.name == tableTag.name) {
                    currentTag.start = tableTag.start;
                    currentTag.end = tableTag.end;
                    currentTag.stdValue = tableTag.stdValue;
                    currentTag.decimalPlaces = tableTag.decimalPlaces;
                }
            }
        }
        else if (currentTag.type == IOTagType::equal) {
            for (const auto& tableTag : m_ioTagTable)
            {
                 // Same name as input type
                 if (currentTag.name == tableTag.name)
                 {
                     currentTag.value = tableTag.value;
                     currentTag.stdValue = tableTag.stdValue;
                     currentTag.decimalPlaces = tableTag.decimalPlaces;
                 }
            }
        }
    }

    if (!m_saveIsNeeded)
        SaveIsNeeded();
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
    XMLParser::AppendNode(doc, infoNode, "text");
    XMLParser::AppendNode(doc, questionCatNode, "idnumber");

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
        XMLParser::AppendNode(doc, feedbackNode, "text");
        rapidxml::xml_node<>* penaltyNode = XMLParser::AppendNode(doc, questionClozeNode, "penalty");
        XMLParser::SetNodeValue(doc, penaltyNode, "0.3333333");
        rapidxml::xml_node<>* hiddenNode = XMLParser::AppendNode(doc, questionClozeNode, "hidden");
        XMLParser::SetNodeValue(doc, hiddenNode, "0");
        XMLParser::AppendNode(doc, questionClozeNode, "idnumber");
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
}

bool MainFrame::CalculateOutputs(bool useInputValue)
{
    std::vector<wxString> errors;
    bool noError = true;

    auto* pModule = LoadPyModule(m_stcPython->GetText(), errors);

    for(auto error : errors) {
        if(error != "") {
            SendToConsole(error);
            noError = false;
        }
    }

    if(!noError)
        return false;

    for(auto& tag : m_ioTagList) {
        if(tag.type == IOTagType::output) {
            wxString str = tag.name;
            wxString partialStr, afterF = "";
            std::vector<wxString> inputs;

            while((partialStr = str.BeforeFirst(' ', &afterF)) != "") {
                inputs.push_back(partialStr);
                str = afterF;
            }

            // Fill inputs with std or values
            bool first = true;
            for(auto& in : inputs) {
                if(!first) {
                    for(auto tagTable : m_ioTagTable) {
                        if(in == tagTable.name) {
                            if(useInputValue)
                                in = wxString::FromCDouble(tagTable.value, tagTable.decimalPlaces);
                            else
                                in = wxString::FromCDouble(tagTable.stdValue, tagTable.decimalPlaces);
                        }
                    }
                } else {
                    first = false;
                }
            }

            RunPythonScript(inputs, pModule, tag, errors);

            for(const auto& error : errors) {
                if(!error.empty()) {
                    SendToConsole(error);
                    noError = false;
                }
            }
        }
        else if (tag.type == IOTagType::equal) {
            for(const auto& tagInput : m_ioTagList)
            {
                if(tagInput.type == IOTagType::input)
                {
                    // Same name as input type
                    if(tag.name == tagInput.name)
                    {
                        tag.value = tagInput.value;
                        tag.stdValue = tagInput.stdValue;
                        tag.decimalPlaces = tagInput.decimalPlaces;
                    }
                }
            }
        }
    }
    if(pModule != nullptr)
        Py_DECREF(pModule);

    return noError;
}

wxString MainFrame::GetHTMLFromCurrentIOs()
{
    wxString htmlCode = m_stcHTML->GetValue();

    // Set inputs and outputs in html
    for(auto tag : m_ioTagList) {
        wxString ioStr = "";
        if (tag.type == IOTagType::input) ioStr = "+";
        if (tag.type == IOTagType::output) ioStr = "-";
        if (tag.type == IOTagType::equal) ioStr = "=";

        wxString strToReplace = "[[" + ioStr + tag.name + "]]";
        if(tag.type == IOTagType::input)
            htmlCode.Replace(strToReplace, wxString::FromDouble(tag.value, tag.decimalPlaces));
        else if (tag.type == IOTagType::output) {
            if (tag.valueType == "double")
            {
                htmlCode.Replace(strToReplace, wxString::FromCDouble(tag.value));
            } else if(tag.valueType == "int")
            {
                htmlCode.Replace(strToReplace, wxString::Format(wxT("%d"), tag.valueInt));
            }
            else if (tag.valueType == "str")
            {
                htmlCode.Replace(strToReplace, tag.valueStr);
            }
        }
        else if (tag.type == IOTagType::equal) {
            htmlCode.Replace(strToReplace, wxString::FromDouble(tag.value, tag.decimalPlaces));
        }
    }
    htmlCode.Replace("\n", "");

    return htmlCode;
}

wxString MainFrame::FormatHTMLAnswers(wxString unformatedHTML)
{
    wxString formatedHTML = unformatedHTML;
    wxStringTokenizer tokenizer(unformatedHTML, "{}");
    while(tokenizer.HasMoreTokens()) {
        wxString token = tokenizer.GetNextToken();
        if(token.Find(":NUMERICAL:") != wxNOT_FOUND) {
            wxStringTokenizer clozeTkn(token, ":");
            std::vector<wxString> clozeValues;
            while(clozeTkn.HasMoreTokens()) {
                clozeValues.push_back(clozeTkn.GetNextToken());
            }
            if(clozeValues.size() != 4) {
                SendToConsole(wxString::Format(wxT("ATENÇÃO! Resposta da questão cloze \"%s\" inserida "
                                                   "incorretamente.\n\tNão foi possível formatar o preview."),
                                  token),
                    wxColour(255, 255, 0));
                return unformatedHTML;
            }

            wxString notaTol = wxString::Format(wxT("Nota = %s; Tolerância = %s"), clozeValues[0], clozeValues[3]);
            wxString response = clozeValues[2];
            if(response.Replace('=', "") == 0) {
                SendToConsole(wxString::Format(wxT("ATENÇÃO! Não foi inserido o '=' na resposta da questão cloze "
                                                   "\"%s\".\n\tNão foi possível formatar o preview."),
                                  token),
                    wxColour(255, 255, 0));
                return unformatedHTML;
            }
            wxString replaceToStr = "<input type = \"text\" style=\"text-align:center;\" data-toggle=\"tooltip\" "
                                    "data-placement=\"top\" title=\"" +
                notaTol + "\" placeholder = \"" + response + "\">";
            formatedHTML.Replace("{" + token + "}", replaceToStr);
        }
    }

    return formatedHTML;
}

void MainFrame::CreateNewCloze()
{
    wxMessageDialog dlg(this, wxT("Essa ação irá apagar todos os dados sem salvar.\nDeseja mesmo fazer isso?"),
        wxT("Atenção!"), wxYES_NO | wxICON_WARNING | wxCENTRE);
    if (dlg.ShowModal() == wxID_NO)
        return;

    m_filePath = "";
    m_fileName = "";
    m_stcPython->SetText("#Escreva o script em python aqui!\n\ndef soma(a, b):\n\treturn a + b");
    m_stcHTML->SetText("<!-- Cole o HTML do Moodle aqui! -->\n[[+t1]] + [[+t2]] = [[-soma t1 t2]]");
    m_richTextCtrlConsole->Clear();

    m_ioTagList.clear();
    m_ioTagTable.clear();

    m_webViewPreview->SetPage("<html><body></body></html>", "");
    m_notebookMain->SetSelection(0);

    FillTable();

    SaveIsNeeded(false);
}

void MainFrame::SaveFile(const bool& saveAs)
{
    if (m_filePath.empty() || saveAs) {
        wxFileDialog saveFileDialog(this, wxT("Salvar arquivo ANTHA"), "", "", "Arquivo ANTHA (*.antha)|*.antha",
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() == wxID_CANCEL)
            return;
        m_filePath = saveFileDialog.GetPath();
        m_fileName = m_filePath.AfterLast('\\').BeforeFirst('.');
    }

    const wxString saveStr = GetStrSave();

    wxTextFile file(m_filePath);
    file.AddLine(saveStr);
    file.Write();
    file.Close();

    SaveIsNeeded(false);
}

void MainFrame::OpenFile()
{
    if (m_saveIsNeeded) {
        wxMessageDialog dlg(
            this, wxT("Existem alterações que não foram salvas.\nDeseja realmente abrir outro arquivo sem salvar?"), wxT("Atenção!"), wxYES_NO | wxICON_WARNING | wxCENTRE);
        if (dlg.ShowModal() == wxID_NO)
            return;
    }

    wxFileDialog openFileDialog(
        this, wxT("Abrir arquivo ANTHA"), "", "", "Arquivo ANTHA (*.antha)|*.antha", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxTextFile file(openFileDialog.GetPath());
    OpenFile(file);
    FormatHTML();
    m_notebookMain->SetSelection(0);

    SaveIsNeeded(false);
    m_justOpenned = true;
}

void MainFrame::ShowAbout()
{
    wxAboutDialogInfo info;
    info.AddDeveloper(wxT("Thales Lima Oliveira"));
    info.SetLicence(wxT("GPL v2"));
    info.SetDescription(wxT("Gerador de questões cloze programáveis para o Moodle\nIcon made by Pixel perfect from "
        "www.flaticon.com\nThis application uses the WebView2 SDK"));
    info.SetName(wxT("Gerador de questões"));
    ::wxAboutBox(info);
}

void MainFrame::SaveIsNeeded(bool isNeeded)
{
    m_saveIsNeeded = isNeeded;
    wxString title = "";

    if (m_saveIsNeeded)
        title += "*";

    title += wxT("Gerador de questões");

    if (!m_fileName.IsEmpty())
        title += " - " + m_fileName;
    
    SetTitle(title);
}

void MainFrame::OnOpenClick(wxCommandEvent& event)
{
    OpenFile();
}
void MainFrame::OnSaveAsClick(wxCommandEvent& event)
{
    SaveFile(true);
}

void MainFrame::OnSaveClick(wxCommandEvent& event)
{
    SaveFile();
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
                ioStrs[2].ToCDouble(&start);
                ioStrs[3].ToCDouble(&end);
                ioStrs[4].ToCDouble(&stdValue);
                ioStrs[5].ToLong(&decimalPlaces);
                ioStrs[6].ToLong(&startPos);
                ioStrs[7].ToLong(&endPos);

                newTag.type = static_cast<IOTagType>(typeID);
                newTag.name = ioStrs[1];
                newTag.start = start;
                newTag.end = end;
                newTag.stdValue = stdValue;
                newTag.decimalPlaces = decimalPlaces;
                newTag.position = std::make_pair<int>(static_cast<int>(startPos), static_cast<int>(endPos));

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
    m_fileName = file.GetName().AfterLast('\\').BeforeFirst('.');

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
    ShowAbout();
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
        else if (tagStr[0] == '=')
            newIOTag.type = IOTagType::equal;
        else {
            SendToConsole(wxT("Erro ao analisar as tags ('+', '-' e '=') de entradas e saídas, verifique o arquivo HTML"));
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
    OpenFile();
}

void MainFrame::OnPreviewRibbonClick(wxRibbonButtonBarEvent& event)
{
    wxString htmlCode = m_stcHTML->GetValue();

    // Set inputs and outputs in html
    for(auto tag : m_ioTagList) {
        wxString ioStr = "";
        if (tag.type == IOTagType::input) ioStr = "+";
        else if (tag.type == IOTagType::output) ioStr = "-";
        else if (tag.type == IOTagType::equal) ioStr = "=";

        wxString strToReplace = "[[" + ioStr + tag.name + "]]";
        if(tag.type == IOTagType::input) {
            htmlCode.Replace(strToReplace, wxString::FromDouble(tag.stdValue, tag.decimalPlaces));
        }
        else if (tag.type == IOTagType::output) {
            if (tag.valueType == "double")
            {
                htmlCode.Replace(strToReplace, wxString::FromCDouble(tag.value));
            }
            else if (tag.valueType == "int")
            {
                htmlCode.Replace(strToReplace, wxString::Format(wxT("%d"), tag.valueInt));
            }
            else if (tag.valueType == "str")
            {
                htmlCode.Replace(strToReplace, tag.valueStr);
            }
        }
        else if (tag.type == IOTagType::equal) {
            htmlCode.Replace(strToReplace, wxString::FromDouble(tag.stdValue, tag.decimalPlaces));
        }
    }
    htmlCode = FormatHTMLAnswers(htmlCode);
    // MathJax
    wxString mathJaxScript =
        "<script src=\"https://polyfill.io/v3/polyfill.min.js?features=es6\"></script>\n<script id=\"MathJax-script\" "
        "async src=\"https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js\"></script>";

    wxString bootstrapCSS =
        "<link rel = \"stylesheet\" href = \"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css\">";
    wxString jquery = "<script src = \"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script>";
    wxString bootstrap =
        "<script src = \"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js\">< / script>";
    wxString enableTootip =
        "<script>\n$(document).ready(function() {\n$('[data-toggle=\"tooltip\"]').tooltip();\n});\n</script>";

    // wxString bootstrapScript = "<script src = \"https://code.jquery.com/jquery-3.2.1.slim.min.js\" integrity =
    // \"sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN\" crossorigin = \"anonymous\">< /
    // script>\n "
    //    "<script src = \"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js\" integrity =
    //    \"sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q\" crossorigin = \"anonymous\">< /
    //    script>\n "
    //    "<script src = \"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js\" integrity =
    //    \"sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl\" crossorigin = \"anonymous\">< /
    //    script>\"";

    // head with scripts
    wxString head = "<head>\n";

    // Moodle IFG stylesheet
    // head += "<link rel=\"stylesheet\" type=\"text/css\" "
    //        "href=\"https://moodle.ifg.edu.br/theme/styles.php/academi/1616615844_1/all\" />\n";

    head += bootstrapCSS + "\n" + jquery + "\n" + bootstrap + "" + mathJaxScript + "\n";
    head += "</head>";
    m_webViewPreview->SetPage("<html>" + head + "<body>" + htmlCode + enableTootip + "</body></html>", "");

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
    SaveFile(true);
}
void MainFrame::OnSaveRibbonClick(wxRibbonButtonBarEvent& event)
{
    SaveFile();
}
void MainFrame::OnWindowClose(wxCloseEvent& event)
{
    if (!m_saveIsNeeded) {
        event.Skip();
        return;
    }
    wxMessageDialog dlg(
        this, wxT("Existem alterações que não foram salvas.\nDeseja realmente sair sem salvar?"), wxT("Atenção!"), wxYES_NO | wxICON_WARNING | wxCENTRE);
    if(dlg.ShowModal() != wxID_NO)
        event.Skip();
}
void MainFrame::OnNewClick(wxCommandEvent& event)
{
    CreateNewCloze();
}
void MainFrame::OnNewRibbonClick(wxRibbonButtonBarEvent& event)
{
    CreateNewCloze();
}
void MainFrame::OnSTCHTMLChanged(wxStyledTextEvent& event)
{
    if (!m_saveIsNeeded && !m_justOpenned)
        SaveIsNeeded();

    event.Skip();
}
void MainFrame::OnSTCPythonChanged(wxStyledTextEvent& event)
{
    if (!m_saveIsNeeded && !m_justOpenned)
        SaveIsNeeded();

    event.Skip();
}
void MainFrame::OnMainFrameIdle(wxIdleEvent& event)
{
    if (m_justOpenned) m_justOpenned = false;
    event.Skip();
}
