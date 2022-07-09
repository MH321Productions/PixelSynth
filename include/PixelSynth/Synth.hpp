#ifndef PS_SYNTH_HPP
#define PS_SYNTH_HPP

#include <random>

enum class SynthType {Sine, Square, Triangle, Sawtooth, Noise};

/**
 * The main Synthesizer interface.
 * It has only one function, which
 * generates the sound.
 */ 
class Synth {
    protected:
        static const float twoPi;
    public:
        /**
         * The abstract sound generator function to be implemented by every Synthesizer
         * @param sample The number of the sample
         * @param absTime The absolute time of the sample
         * @param relTime The time of the sample in the current frequency period (between 0 and 1)
         * @param freq The frequency of the sound
         * @returns a float value between -1 and 1
         */ 
        virtual float generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq) = 0;
};

/**
 * A Sine wave generator
 */ 
class SineSynth: public virtual Synth {
    public:
        virtual float generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq);
};

/**
 * A Square wave generator
 *          ___     ___
 *      ___|   |___|
 * 
 */ 
class SquareSynth: public virtual Synth {
    public:
        virtual float generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq);
};

/**
 * A Triangular wave generator
 * 
 *       /\  /\  /\
 *      /  \/  \/  \
 * 
 */ 
class TriangleSynth: public virtual Synth {
    private:
        static const float quarter, two, threeQuarters, four;
    public:
        virtual float generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq);
};

/**
 * A Sawtooth wave generator
 * 
 *       /| /| /| /|
 *      / |/ |/ |/ |
 * 
 */ 
class SawSynth: public virtual Synth {
    private:
        static const float two;
        
    public:
        virtual float generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq);
};

/**
 * A Noise generator
 */ 
class NoiseSynth: public virtual Synth {
    private:
        std::mt19937_64 gen;

    public:
        NoiseSynth();

        virtual float generate(const unsigned long& sample, const float& absTime, const float& relTime, const unsigned int& freq);
};

#endif //PS_SYNTH_HPP