#include <iostream>
#include "SDL.h"
#include "SDL_audio.h"

using namespace std;

static uint64_t totalSamples = 0;

void fillBuffer(void* userdata, Uint8* stream, int length);

int main() {
    cout << "Starting sinewave test" << endl;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "Couldn't start SDL Audio: " << SDL_GetError() << endl;
        return 1;
    }

    cout << "SDL initialized" << endl;

    cout << "Using audio driver: " << SDL_GetCurrentAudioDriver() << endl;

    cout << "Available audio devices:" << endl;
    for (int i = 0; i < SDL_GetNumAudioDevices(0); i++) {
        cout << "Testing device " << i << ": " << SDL_GetAudioDeviceName(i, 0) << flush;
    

        SDL_AudioSpec spec, real;
        SDL_AudioDeviceID dev;

        if (SDL_GetAudioDeviceSpec(i, 0, &spec) != 0) {
            cerr << "Couldn't get device specs: " << SDL_GetError() << endl;
            return 1;
        }

        spec.freq = 48000;
        spec.format = AUDIO_S16SYS;
        spec.samples = 4096;
        spec.callback = fillBuffer;

        dev = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, 0), 0, &spec, NULL, 0);
        if (dev == 0) {
            cerr << "Couldn't open the device: " << SDL_GetError() << endl;
            return 1;
        }

        SDL_PauseAudioDevice(dev, 0);
        SDL_Delay(2000);
        cout << " -- finished" << endl;
        SDL_CloseAudioDevice(dev);
    }

    SDL_Quit();

    return 0;
}

void fillBuffer(void* userdata, Uint8* stream, int length) {
    Sint16* buffer = (Sint16*) stream;
    int samples = length / sizeof(Sint16);

    SDL_memset(stream, 0, length);

    for (int i = 0; i < samples; i += 2) {
        float time = (float) totalSamples / 48000;
        int freq = 440; //Sample Frequency: a
        int amp = SDL_MAX_SINT16;

        Sint16 value = (Sint16)(SDL_sin(6.283185f * time * freq) * amp);
        buffer[i] = value;
        buffer[i + 1] = value;
        totalSamples++;
    }
}