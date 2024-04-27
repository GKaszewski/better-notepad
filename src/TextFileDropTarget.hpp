#ifndef BETTER_NOTEPAD_TEXTFILEDROPTARGET_HPP
#define BETTER_NOTEPAD_TEXTFILEDROPTARGET_HPP

#include <wx/wxprec.h>

#ifndef WX_PRECOMP

#include <wx/wx.h>

#endif

#include <wx/dnd.h>

class TextFileDropTarget : public wxFileDropTarget {
public:
    TextFileDropTarget(wxTextCtrl *owner);

    bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &filenames) override;

private:
    wxTextCtrl *owner;
};


#endif //BETTER_NOTEPAD_TEXTFILEDROPTARGET_HPP
