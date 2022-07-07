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

    /*cout << "Available drivers: " << endl;
    for (int i = 0; i < SDL_GetNumAudioDrivers(); i++) {
        cout << i << ": " << SDL_GetAudioDriver(i) << endl;
    }*/

    cout << "Using audio driver: " << SDL_GetCurrentAudioDriver() << endl;

    cout << "Available audio devices:" << endl;
    for (int i = 0; i < SDL_GetNumAudioDevices(0); i++) {
        cout << i << ": " << SDL_GetAudioDeviceName(i, 0) << endl;
    }

    /*cout << "Choose a device: ";
    int index;
    cin >> index;

    if (index < 0 || index >= SDL_GetNumAudioDevices(0)) {
        cerr << "Invalid index" << endl;
        return 1;
    }*/

    SDL_AudioSpec spec;
    SDL_AudioDeviceID dev;

    if (SDL_GetAudioDeviceSpec(0, 0, &spec) != 0) {
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

    cout << "Start playing" << endl;
    SDL_PauseAudioDevice(dev, 0);
    SDL_Delay(2000);
    cout << "Stop playing" << endl;
    SDL_CloseAudioDevice(dev);

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