#include "ExportClose.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>

ExportClose::ExportClose(wxWindow* parent)
    : ExportCloseBase(parent)
{
    SetTitle(wxT("Exportar questões"));
    m_staticTextNumQuiz->SetLabel(wxT("Número de questões"));
    SetSize(GetBestSize());
    Layout();
}

ExportClose::~ExportClose()
{
}

void ExportClose::OnCancelClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
void ExportClose::OnExportClick(wxCommandEvent& event)
{
    m_catName = m_textCtrlCatName->GetValue();
    if(m_catName == "") {
        wxMessageDialog dialog(this, wxT("Insira o nome da categoria."), wxT("Erro"), wxICON_ERROR);
        dialog.ShowModal();
        return;
    }
    long numQuiz = 0;
    if(!m_textCtrlNumQuiz->GetValue().ToLong(&numQuiz)) {
        wxMessageDialog dialog(this, wxT("Dado inserido incorretamente em 'Número de questões'."), wxT("Erro"), wxICON_ERROR);
        dialog.ShowModal();
        return;
    }
    m_numQuiz = numQuiz;
    if(m_numQuiz <= 0) {
        wxMessageDialog dialog(this, wxT("Insira um número maior que zero em 'Número de questões'."), wxT("Erro"), wxICON_ERROR);
        dialog.ShowModal();
        return;
    }

    wxFileDialog saveFileDialog(this, wxT("Salvar arquivo XML"), "", "", "Arquivo XML (*.xml)|*.xml",
                                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(saveFileDialog.ShowModal() == wxID_CANCEL) return;

    m_path = saveFileDialog.GetPath();
    
    EndModal(wxID_OK);
}
