#include <iostream>
#include "SDL.h"
#include "PixelSynth/Hardware.hpp"
#include "PixelSynth/Mixer.hpp"

using namespace std;

HardwareHandler* HardwareHandler::instance = NULL;

HardwareHandler* HardwareHandler::getHandler() {
    if (instance) return instance;

    instance = new HardwareHandler;
    if (instance->init()) return instance;

    return NULL;
}

HardwareHandler::~HardwareHandler() {
    instance = NULL;
    if (activeDevice) activeDevice->close();
}

bool HardwareHandler::init() {
    //Init SDL
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        cerr << "Couldn't init SDL: " << SDL_GetError() << endl;
        return false;
    }

    //Search for audio devices
    int success = 0;
    for (int i = 0; i < SDL_GetNumAudioDevices(0); i++) {
        Device d(SDL_GetAudioDeviceName(i, 0), i);
        if (d.init()) {
            devices.push_back(d);
            success++;
        }
    }

    cout << success << " audio devices registered" << endl;

    return success;
}

bool HardwareHandler::checkForDeviceChanges() {
    bool changed = false;
    while (SDL_PollEvent(&event)) {
        //TODO: Process Event changes
        if (event.type == SDL_AUDIODEVICEADDED) {
            changed = true;
        } else if (event.type == SDL_AUDIODEVICEREMOVED) {
            changed = true;
        }
    }

    return changed;
}

void HardwareHandler::setMixer(Mixer* mixer) {
    this->mixer = mixer;
    if (mixer) mixer->setHardware(this);
}

bool HardwareHandler::setActiveDevice(const Device& device) {
    for (int i = 0; i < devices.size(); i++) {
        if (devices.at(i) == device) return setActiveDevice(i);
    }

    return false;
}

bool HardwareHandler::setActiveDevice(const int& index) {
    if (index < 0 || index >= devices.size() || !mixer) return false;

    if (activeDevice) activeDevice->close();

    activeDevice = &devices.at(index);
    if (!activeDevice->open(mixer)) {
        activeDevice = NULL;
        return false;
    }

    cout << "Active device: " << activeDevice->name << "\nChannels: " << activeDevice->channels << endl;

    return true;
}
