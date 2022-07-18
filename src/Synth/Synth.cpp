#include <iostream>
#include <cmath>
#include <chrono>
#include "PixelSynth/Synth.hpp"
#include "PixelSynth/Hardware.hpp"

using namespace std;
using namespace chrono;

const float Synth::twoPi = 6.283185f;

//------------------------------------------------------------------------------------------------------------
//SineSynth
float SineSynth::generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq) {
    return sin(twoPi * absTime * freq);
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//SquareSynth
float SquareSynth::generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq) {
    float s = sin(twoPi * absTime * freq);
    return (s < 0) ? -1.0f : (s == 0) ? 0.0f : 1.0f; //Use sign of sine to create square
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//TriangleSynth
float TriangleSynth::generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq) {
    return 2.0f * abs(2.0f * (absTime * freq - floor(absTime * freq + 0.5f))) - 1.0f;
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//SawSynth
float SawSynth::generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq) {
    return 2.0f * (absTime * freq - floor(absTime * freq + 0.5f));
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//NoiseSynth
NoiseSynth::NoiseSynth() {
    gen.seed(system_clock::now().time_since_epoch().count());
}

float NoiseSynth::generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq) {
    return gen() / (float) INT32_MAX; //Random values between -1 and 1
}
//------------------------------------------------------------------------------------------------------------