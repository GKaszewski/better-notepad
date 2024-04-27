#include "TextFileDropTarget.hpp"

TextFileDropTarget::TextFileDropTarget(wxTextCtrl *owner) : owner(owner) {}

bool TextFileDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &filenames) {
    wxString filename;
    for (const auto &file : filenames) {
        filename = file;
    }
    owner->LoadFile(filename);
    return true;
}
