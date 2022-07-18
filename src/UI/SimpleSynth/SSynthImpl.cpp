#include <iostream>
#include <wx/wx.h>
#include "SSynthImpl.hpp"
#include "UI/ImageHandler/ImageHandler.hpp"
#include "PixelSynth/Hardware.hpp"
#include "PixelSynth/Mixer.hpp"

using namespace std;

#define checkActive if (!active) return

class SSynthApp : public wxApp {
    public:
        virtual bool OnInit() {
            SSynthFrameImpl* frame = new SSynthFrameImpl;
            frame->Show(true);
            return true;
        }
};

wxIMPLEMENT_APP(SSynthApp);

SSynthFrameImpl::SSynthFrameImpl() : SSynthFrame(NULL) {
    imgSine = ImageHandler::loadImage(ImageType::SineWave);
    imgSquare = ImageHandler::loadImage(ImageType::SquareWave);
    imgTriangle = ImageHandler::loadImage(ImageType::TriangleWave);
    imgSaw = ImageHandler::loadImage(ImageType::SawWave);
    imgNoise = ImageHandler::loadImage(ImageType::NoiseWave);
    imgSineSelected = ImageHandler::loadImage(ImageType::SineWaveSelected);
    imgSquareSelected = ImageHandler::loadImage(ImageType::SquareWaveSelected);
    imgTriangleSelected = ImageHandler::loadImage(ImageType::TriangleWaveSelected);
    imgSawSelected = ImageHandler::loadImage(ImageType::SawWaveSelected);
    imgNoiseSelected = ImageHandler::loadImage(ImageType::NoiseWaveSelected);

    btnSine->SetBitmap({imgSineSelected});
    btnSquare->SetBitmap({imgSquare});
    btnTriangle->SetBitmap({imgTriangle});
    btnSaw->SetBitmap({imgSaw});
    btnNoise->SetBitmap({imgNoise});

    hardware = HardwareHandler::getHandler();
    if (!hardware) {
        wxLogError(wxT("Couldn't start hardware handler"));
        active = false;
        return;
    }

    mixer = new SimpleMixer;
    mixer->setFrequency(440);
    hardware->setMixer(mixer);

    for (Device& d: hardware->devices) {
        cmbDevice->Append(wxString::FromUTF8(d.name.c_str()));
    }
    cmbDevice->SetSelection(0);

    if (!hardware->setActiveDevice(0)) {
        wxLogError(wxT("Couldn't open audio device"));
        active = false;
        return;
    }

    hardware->getActiveDevice().play();
}

void SSynthFrameImpl::onIdle(wxIdleEvent& event) {
    checkActive;

    if (hardware->checkForDeviceChanges()) {

    }
}

void SSynthFrameImpl::onFreq(wxCommandEvent& event) {
    freq = sliderFreq->GetValue();
    wxString text;
    text << freq << " Hz";
    lblFreq->SetLabel(text);

    checkActive;
    mixer->setFrequency(freq);
}

void SSynthFrameImpl::onDeviceSelect(wxCommandEvent& event) {
    checkActive;

    int index = cmbDevice->GetSelection();
    
    if (!hardware->setActiveDevice(index)) wxLogError(wxT("Couldn't change device"));
    hardware->getActiveDevice().play();
}

void SSynthFrameImpl::onSine(wxCommandEvent& event) {
    unselectButtons();
    btnSine->SetBitmap({imgSineSelected});
    updateMixer(SynthType::Sine);
}

void SSynthFrameImpl::onSquare(wxCommandEvent& event) {
    unselectButtons();
    btnSquare->SetBitmap({imgSquareSelected});
    updateMixer(SynthType::Square);
}

void SSynthFrameImpl::onTriangle(wxCommandEvent& event) {
    unselectButtons();
    btnTriangle->SetBitmap({imgTriangleSelected});
    updateMixer(SynthType::Triangle);
}

void SSynthFrameImpl::onSaw(wxCommandEvent& event) {
    unselectButtons();
    btnSaw->SetBitmap({imgSawSelected});
    updateMixer(SynthType::Sawtooth);
}

void SSynthFrameImpl::onNoise(wxCommandEvent& event) {
    unselectButtons();
    btnNoise->SetBitmap({imgNoiseSelected});
    sliderFreq->Disable();
    updateMixer(SynthType::Noise);
}

void SSynthFrameImpl::updateMixer(SynthType type) {
    checkActive;

    synth = type;
    mixer->setSynth(type);
}

void SSynthFrameImpl::unselectButtons() {
    btnSine->SetBitmap({imgSine});
    btnSquare->SetBitmap({imgSquare});
    btnTriangle->SetBitmap({imgTriangle});
    btnSaw->SetBitmap({imgSaw});
    btnNoise->SetBitmap({imgNoise});
    sliderFreq->Enable();
}