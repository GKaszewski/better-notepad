#include "App.hpp"
#include "Frame.hpp"

bool App::OnInit() {
    Frame* frame = new Frame("Better Notepad", wxPoint(50, 50), wxSize(600, 400));
    frame->Show(true);

    frame->SetIcon(wxICON(ApplicationIcon));

    if (argc > 1) {
        wxString filePath = argv[1];
        frame->LoadFile(filePath);
    }

    return true;
}
