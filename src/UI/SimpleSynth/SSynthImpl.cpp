#include <iostream>
#include <wx/app.h>
#include "SSynthImpl.hpp"

using namespace std;

class SSynthApp : public wxApp {
    public:
        virtual bool OnInit() {
            SSynthFrameImpl* frame = new SSynthFrameImpl;
            frame->Show(true);
            return true;
        }
};

wxIMPLEMENT_APP(SSynthApp);