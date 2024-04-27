#include <algorithm>

#include "Frame.hpp"
#include "wx/wfstream.h"
#include "wx/txtstrm.h"
#include "TextFileDropTarget.hpp"

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(Frame::ID_Hello, Frame::OnHello)
    EVT_MENU(Frame::ID_EXIT, Frame::OnExit)
    EVT_MENU(Frame::ID_NEW, Frame::OnNew)
    EVT_MENU(Frame::ID_OPEN, Frame::OnOpen)
    EVT_MENU(Frame::ID_SAVE, Frame::OnSave)
wxEND_EVENT_TABLE()

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size): wxFrame(nullptr, wxID_ANY, title, pos, size) {
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(Frame::ID_NEW, "&New...\tCtrl-N", "Create a new file");
    menuFile->Append(Frame::ID_OPEN, "&Open...\tCtrl-O", "Open a file");
    menuFile->Append(Frame::ID_SAVE, "&Save...\tCtrl-S", "Save a file");
    menuFile->AppendSeparator();
    menuFile->Append(Frame::ID_EXIT, "Exit");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to Better Notepad!");

    textCtrl = new wxTextCtrl(this, Frame::ID_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    SetSizeHints(400, 300);

    TextFileDropTarget* dropTarget = new TextFileDropTarget(textCtrl);
    textCtrl->SetDropTarget(dropTarget);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(textCtrl, 1, wxEXPAND | wxALL);
    SetSizer(sizer);
    Layout();

//    searchCtrl = new wxTextCtrl(this, wxID_ANY);
//    searchButton = new wxButton(this, wxID_ANY, wxT("Search"));
//    searchButton->Bind(wxEVT_BUTTON, &Frame::OnFind, this);
//    matchCaseCheckBox = new wxCheckBox(this, wxID_ANY, wxT("Match Case"));
//
//    matchCaseCheckBox->Bind(wxEVT_CHECKBOX, &Frame::OnMatchCaseChecked, this);
//
//    wxBoxSizer* searchSizer = new wxBoxSizer(wxHORIZONTAL);
//    searchSizer->Add(searchCtrl, 1, wxEXPAND | wxALL);
//    searchSizer->Add(searchButton, 0, wxEXPAND | wxALL);
//    searchSizer->Add(matchCaseCheckBox, 0, wxEXPAND | wxALL);
//    sizer->Add(searchSizer, 0, wxEXPAND | wxALL);
//    SetSizer(sizer);
//    Layout();
}

void Frame::OnHello(wxCommandEvent &event) {
    wxMessageBox("Hello world from Better Notepad!", "About Better Notepad", wxOK | wxICON_INFORMATION);
}

void Frame::OnExit(wxCommandEvent &event) {
    Close(true);
}

void Frame::OnOpen(wxCommandEvent &event) {
    wxFileDialog openFileDialog(this, _("Open a file"), "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    LoadFile(openFileDialog.GetPath());
}

void Frame::OnSave(wxCommandEvent &event) {
    wxFileDialog saveFileDialog(this, _("Save a file"), "", "", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxFileOutputStream output_stream(saveFileDialog.GetPath());
    if (!output_stream.IsOk()) {
        wxLogError("Cannot save current contents to file '%s'.", saveFileDialog.GetPath());
        return;
    }

    wxString file_contents = textCtrl->GetValue();
    wxTextOutputStream text_stream(output_stream);
    text_stream.WriteString(file_contents);
}

void Frame::OnNew(wxCommandEvent &event) {
    textCtrl->Clear();
}

void Frame::OnFind(wxCommandEvent &event) {
    SearchText();
}

void Frame::SearchText() {
    wxString searchText = searchCtrl->GetValue();
    wxString content = textCtrl->GetValue();

    if (searchText.IsEmpty()) {
        wxMessageBox(wxT("Please enter a search text!"), wxT("Search Result"), wxICON_INFORMATION | wxOK);
        return;
    }

    if (lastSearchText != searchText) {
        searchPositions.clear();
        lastSearchText = searchText;
    }

    if (!matchCaseCheckBox->IsChecked()) {
        searchText.MakeLower();
        content.MakeLower();
    }

    int pos = content.find(searchText);
    textCtrl->SetSelection(pos, pos + searchText.length());
    textCtrl->SetFocus();

    while (pos != wxNOT_FOUND) {
        searchPositions.push_back(pos);
        pos = content.find(searchText, pos + searchText.length());
    }

    if (searchPositions.empty()) {
        wxMessageBox(wxT("No matches found!"), wxT("Search Result"), wxICON_INFORMATION | wxOK);
        return;
    }
}

void Frame::OnMatchCaseChecked(wxCommandEvent &event) {
    SearchText();
}

void Frame::LoadFile(const wxString &filename) {
    wxFileInputStream input_stream(filename);
    if (!input_stream.IsOk()) {
        wxLogError("Cannot open file '%s'.", filename);
        return;
    }

    wxString file_contents;
    wxTextInputStream text_stream(input_stream);
    while (!input_stream.Eof()) {
        file_contents += text_stream.ReadLine() + "\n";
    }
    textCtrl->SetValue(file_contents);
}
