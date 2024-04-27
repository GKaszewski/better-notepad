#ifndef BETTER_NOTEPAD_APP_HPP
#define BETTER_NOTEPAD_APP_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class App : public wxApp {
public:
    bool OnInit() override;
};


#endif //BETTER_NOTEPAD_APP_HPP
