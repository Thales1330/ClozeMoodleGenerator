#ifndef EXPORTCLOSE_H
#define EXPORTCLOSE_H
#include "wxcrafter.h"

class ExportClose : public ExportCloseBase
{
public:
    ExportClose(wxWindow* parent);
    virtual ~ExportClose();
    
    wxString m_catName = "CatName";
    int m_numQuiz = 30;
    wxString m_path = "";
    
protected:
    virtual void OnCancelClick(wxCommandEvent& event);
    virtual void OnExportClick(wxCommandEvent& event);
};
#endif // EXPORTCLOSE_H
