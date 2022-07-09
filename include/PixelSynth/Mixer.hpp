#ifndef PS_MIXER_HPP
#define PS_MIXER_HPP

#include "PixelSynth/Synth.hpp"

class Device;           //Hardware.hpp
class HardwareHandler;  //Hardware.hpp

/**
 * The mixer handles the communication between the 
 * Synthesizer(s) and the audio API by implementing
 * the SDL_audio callback function. The class is abstract
 * to enable the use of different mixers for different
 * purposes.
 */ 
class Mixer {
    friend class Device;
    friend class HardwareHandler;
    private:
        /**
         * This method gets called by SDL and redirects to the correct method
         */ 
        static void fillBuffer(void* userdata, unsigned char* stream, int length);

        void setHardware(HardwareHandler* hardware);

    protected:
        static const int maxAmp;    //Maximum amplifier for maximal volume
        unsigned long totalSamples;
        float time, relTime, volume;
        int amp, freq, periodTime;
        HardwareHandler* hardware;

        /**
         * The method that fills the SDL audio callback buffer.
         */ 
        virtual void fillBuffer(short* buffer, const int& length, const int& samples) = 0;
        void calculateTimes();

    public:
        Mixer(): totalSamples(0), time(0.0f), relTime(0.0f), volume(0.0f), amp(0), freq(0), periodTime(0), hardware(NULL) {}

        float getVolume();
        void setVolume(const float& volume);
        int getFrequency();
        void setFrequency(const int& frequency);
};

/**
 * A simple mixer designed to play one mono
 * tone with one Synth at one frequency
 */ 
class SimpleMixer: public virtual Mixer {
    private:
        SineSynth sine;
        SquareSynth square;
        TriangleSynth triangle;
        SawSynth saw;
        NoiseSynth noise;
        SynthType currentSynth;

        float getTone();

    protected:
        virtual void fillBuffer(short* buffer, const int& length, const int& samples);
    
    public:
        SynthType getSynth();
        void setSynth(SynthType type);
};

#endif //PS_MIXER_HPP