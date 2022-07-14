#ifndef PS_SSYNTH_IMPL_HPP
#define PS_SSYNTH_IMPL_HPP

#include "SSynth.h"
#include "PixelSynth/Synth.hpp"
#include <wx/wx.h>
#include <wx/image.h>

class HardwareHandler;
class SimpleMixer;

class SSynthFrameImpl : public virtual SSynthFrame {
    private:

        HardwareHandler* hardware;
        SimpleMixer* mixer;
        SynthType synth;

        wxImage imgSine, imgSquare, imgTriangle, imgSaw, imgNoise;
        wxImage imgSineSelected, imgSquareSelected, imgTriangleSelected, imgSawSelected, imgNoiseSelected;
        int freq;
        bool active = true;

        virtual void onIdle(wxIdleEvent& event);
        virtual void onFreq(wxCommandEvent& event);
        virtual void onDeviceSelect(wxCommandEvent& event);
        virtual void onSine(wxCommandEvent& event);
        virtual void onSquare(wxCommandEvent& event);
        virtual void onTriangle(wxCommandEvent& event);
        virtual void onSaw(wxCommandEvent& event);
        virtual void onNoise(wxCommandEvent& event);

        void updateMixer(SynthType type);
        void unselectButtons();

    public:
        SSynthFrameImpl();
};

#endif //PS_SSYNTH_IMPL_HPP