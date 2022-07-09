#include <iostream>
#include <cmath>
#include <chrono>
#include "PixelSynth/Synth.hpp"

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
    return (s < 0) ? -1.0f : 1.0f; //Use sign of sine to create square
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//TriangleSynth
const float TriangleSynth::quarter = 0.25f;
const float TriangleSynth::threeQuarters = 0.75f;
const float TriangleSynth::two = 2.0f;
const float TriangleSynth::four = 4.0f;

float TriangleSynth::generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq) {
    if (relTime > quarter && relTime <= threeQuarters) {
        return two - (relTime * -four);
    } else if (relTime > threeQuarters) {
        return (relTime * four) - four;
    } else {
        return relTime * four;
    }
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//SawSynth
const float SawSynth::two = 2.0f;
float SawSynth::generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq) {
    float normal = relTime * 2.0f;
    if (relTime > 0.5f) normal -= 2.0f;

    return normal;
}
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//NoiseSynth
NoiseSynth::NoiseSynth() {
    gen.seed(system_clock::now().time_since_epoch().count());
}

float NoiseSynth::generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq) {
    return 0.0f; //TODO: Implement Noise generator
}
//------------------------------------------------------------------------------------------------------------