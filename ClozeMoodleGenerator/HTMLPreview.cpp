#include "HTMLPreview.h"

HTMLPreview::HTMLPreview(wxWindow* parent, wxString code)
    : HTMLPreviewBase(parent)
{
    m_webView->SetPage("<html><body>" + code + "</html></body>", "");
}

HTMLPreview::~HTMLPreview()
{
}

