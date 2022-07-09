#include <cstring>
#include <algorithm>
#include "PixelSynth/Mixer.hpp"
#include "PixelSynth/Hardware.hpp"

using namespace std;

const int Mixer::maxAmp = 32767; //Maximal signed 16 Bit value

void Mixer::fillBuffer(void* userdata, unsigned char* stream, int length) {
    memset(stream, 0, length);

    if (!userdata) return;

    short* buffer = (short*) stream;
    int samples = length / sizeof(short);

    Mixer* mix = (Mixer*) userdata;
    mix->fillBuffer(buffer, length, samples);
}

void Mixer::setHardware(HardwareHandler* hardware) {
    this->hardware = hardware;
}

float Mixer::getVolume() {
    return volume;
}

void Mixer::setVolume(const float& volume) {
    this->volume = clamp(volume, 0.0f, 1.0f);
    amp = this->volume * maxAmp;
}

int Mixer::getFrequency() {
    return freq;
}

void Mixer::setFrequency(const int& frequency) {
    freq = clamp(frequency, 0, (int) DeviceSpecValues::Frequency);
    periodTime = DeviceSpecValues::Frequency / freq;
}


void Mixer::calculateTimes() {
    time = (float) totalSamples / DeviceSpecValues::Frequency;
    relTime = (float) (totalSamples % periodTime) / periodTime;
}