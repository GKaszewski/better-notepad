#ifndef BETTER_NOTEPAD_TEXTMANAGER_HPP
#define BETTER_NOTEPAD_TEXTMANAGER_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/file.h>

class TextManager {
public:
    TextManager(const wxString& filePath);
    wxString LoadInitialChunk();
    wxString LoadNextChunk();
    wxString LoadPreviousChunk();

private:
    wxFile file;
    long currentPosition;
    size_t chunkSize;
    wxString filePath;

    wxString LoadChunk(long position);

};


#endif //BETTER_NOTEPAD_TEXTMANAGER_HPP
