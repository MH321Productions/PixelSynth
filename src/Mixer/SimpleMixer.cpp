#include "PixelSynth/Mixer.hpp"
#include "PixelSynth/Hardware.hpp"

void SimpleMixer::fillBuffer(short* buffer, const int& length, const int& samples) {
    //Send the same tone to each channel
    int channels = hardware->getActiveDevice().channels;
    for (int i = 0; i < samples; i += channels) {
        short value = (short) (getTone() * maxAmp);

        for (int j = 0; j < channels; j++) {
            buffer[i + j] = value;
        }
    }
}

SynthType SimpleMixer::getSynth() {
    return currentSynth;
}

void SimpleMixer::setSynth(SynthType synth) {
    currentSynth = synth;
}

float SimpleMixer::getTone() {
    switch (currentSynth) {
        case SynthType::Square:     return square.generate(totalSamples, time, relTime, freq);
        case SynthType::Triangle:   return triangle.generate(totalSamples, time, relTime, freq);
        case SynthType::Sawtooth:   return saw.generate(totalSamples, time, relTime, freq);
        case SynthType::Noise:      return noise.generate(totalSamples, time, relTime, freq);
        default: /*Sine*/           return sine.generate(totalSamples, time, relTime, freq);
    }
}