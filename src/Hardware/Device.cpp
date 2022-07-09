#include <iostream>
#include "SDL.h"
#include "PixelSynth/Hardware.hpp"
#include "PixelSynth/Mixer.hpp"

using namespace std;

Device::Device(const string& name, const int& id): name(name), id(id), channels(-1), isOpen(false), isRunning(false) {}

bool Device::init() {
    if (SDL_GetAudioDeviceSpec(id, 0, &spec) != 0) {
        cerr << "Couldn't get specs of device " << id << endl;
        return false;
    }

    spec.freq = DeviceSpecValues::Frequency;
    spec.format = DeviceSpecValues::Format;
    spec.samples = DeviceSpecValues::Samples;
    channels = spec.channels;

    return true;
}

bool Device::open(Mixer* mixer) {
    if (isOpen) return true;

    //Set spec data to given Mixer
    spec.userdata = mixer;
    spec.callback = &Mixer::fillBuffer;

    dev = SDL_OpenAudioDevice(name.c_str(), 0, &spec, NULL, 0);
    if (!dev) {
        cerr << "Couldn't open audio device: " << SDL_GetError() << endl;
        return false;
    }

    channels = spec.channels;

    isOpen = true;
    isRunning = false;
    return true;
}

void Device::close() {
    if (!isOpen) return;

    SDL_CloseAudioDevice(dev);
    isOpen = false;
    isRunning = false;
}

void Device::pause() {
    if (!isOpen || !isRunning) return;

    SDL_PauseAudioDevice(dev, 1);
    isRunning = false;
}

void Device::play() {
    if (!isOpen || isRunning) return;

    SDL_PauseAudioDevice(dev, 0);
    isRunning = true;
}


bool Device::operator == (const Device& other) const {
    return name == other.name && id == other.id;
}
