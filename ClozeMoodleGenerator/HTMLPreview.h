#ifndef HTMLPREVIEW_H
#define HTMLPREVIEW_H
#include "wxcrafter.h"

class HTMLPreview : public HTMLPreviewBase
{
public:
    HTMLPreview(wxWindow* parent, wxString code);
    virtual ~HTMLPreview();
};
#endif // HTMLPREVIEW_H
