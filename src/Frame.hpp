#ifndef BETTER_NOTEPAD_FRAME_HPP
#define BETTER_NOTEPAD_FRAME_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "TextManager.hpp"

#endif


class Frame : public wxFrame {
public:
    Frame(const wxString& title, const wxPoint& pos, const wxSize& size);

    enum {
        ID_Hello = 1,
        ID_EXIT = 2,
        ID_TEXT_CTRL = 3,
        ID_NEW = 4,
        ID_OPEN = 5,
        ID_SAVE = 6,
        ID_FIND = 7,
    };

    void LoadFile(const wxString& filename);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnFind(wxCommandEvent& event);

    void OnMatchCaseChecked(wxCommandEvent& event);
    void SearchText();

    wxTextCtrl* textCtrl;
    wxTextCtrl* searchCtrl;
    wxButton* searchButton;
    wxCheckBox* matchCaseCheckBox;

    std::vector<int> searchPositions;
    wxString lastSearchText;

    wxDECLARE_EVENT_TABLE();
};


#endif //BETTER_NOTEPAD_FRAME_HPP
