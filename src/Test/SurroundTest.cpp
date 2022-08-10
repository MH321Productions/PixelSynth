#include <iostream>
#include <chrono>
#include <map>
#include <vector>
#include <string>
#include <array>
#include "SDL.h"
#define IH_USE_SDL
#include "UI/ImageHandler/ImageHandler.hpp"

using namespace std;
using namespace chrono;

//Global variables
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* speakerTex;
SDL_Rect speakerPos {0, 0, 600, 600}, volume {0, 0, 48, 0};
bool running = true;
double deltaTime = 0.0, angle = 0.0, totalTime = 0.0, nextTime = 4.0;
time_point<system_clock> start, endTime;
duration<double> d;
int devIndex = 0;
SDL_AudioSpec dev;
SDL_AudioDeviceID openDevice = 0;
string devName;
const int freqMax = 48000;
bool autoMode = false, rightPressed = false, leftPressed = false;
const double twoPi = 2 * 3.14159265358979323846264338327950288;
size_t totalSamples = 0;

/**
 * An enum containing all channels
 */ 
enum Channels: unsigned char {FL, FR, C, Sub, BL, BR, SL, SR, BC};

/**
 * This array contains the names for the different
 * channel modes
 */ 
static const array<string, 9> modeNames = {"(unknown)", "(Mono)", "(Stereo)", "(2.1)", "(Quad)", "(4.1)", "(5.1)", "(6.1)", "(7.1)"};

/**
 * This array contains the channel indices for
 * the different channel modes
 */ 
static const array<array<int, 9>, 9> channelConfigs = {{
    {-1, -1, -1, -1, -1, -1, -1, -1, -1},   //Unknown
    {-1, -1, 0, -1, -1, -1, -1, -1, -1},    //Mono
    {0, 1, -1, -1, -1, -1, -1, -1, -1},     //Stereo
    {0, 1, -1, 2, -1, -1, -1, -1, -1},      //2.1
    {0, 1, -1, -1, 2, 3, -1, -1, -1},       //Quad
    {0, 1, -1, 2, 3, 4, -1, -1, -1},        //4.1
    {0, 1, 2, 3, 4, 5, -1, -1, -1},         //5.1
    {0, 1, 2, 3, -1, -1, 5, 6, 4},          //6.1
    {0, 1, 2, 3, 4, 5, 6, 7, -1}            //7.1
}};

/**
 * This array maps the channels to angles in the room
 * (except the subwoofer, which has no angle)
 */ 
static const array<double, 9> channelAngles = {315.0, 45.0, 0.0, -1.0, 225.0, 135.0, 270.0, 90.0, 180.0};

static const array<SDL_Rect, 9> channelPositions = {{
    {712, 37, 50, 150},
    {1038, 37, 50, 150},
    {876, 37, 50, 150},
    {0, 0, 0, 0},
    {712, 412, 50, 150},
    {1038, 412, 50, 150},
    {712, 225, 50, 150},
    {1038, 225, 50, 150},
    {876, 412, 50, 150}
}};

/**
 * This array saves the calculated volumes of the channels
 * (the subwoofer is always zero)
 */ 
static array<double, 9> channelVolumes = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

//Functions
void mainLoop();
void fillBuffer(void* userdata, Uint8* stream, int len);
void calculateDeltaTime(const bool& startFrame);
void printDevSpecs();
void drawVolumes();
void calculateVolumes();
bool setActiveDevice(const int& index);

int main(int count, char** args) {
    cout << "Starting surround test";
    if (count > 1 && !SDL_strcmp(args[1], "auto")) {
        cout << " (auto mode)";
        autoMode = true;
    }
    cout << endl;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) {
        cerr << "Couldn't init SDL: " << SDL_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow("Surround test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window) {
        cerr << "Couldn't create window: " << SDL_GetError() << endl;
        return 1;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Couldn't create renderer: " << SDL_GetError() << endl;
        return 1;
    }

    speakerTex = ImageHandler::loadImage(ImageType::SpeakerCircle, renderer);
    if (!speakerTex) {
        cerr << "Couldn't load texture" << endl;
        return 1;
    }

    cout << "\nPossible audio devices: \n";
    for (int i = 0; i < SDL_GetNumAudioDevices(0); i++) {
        cout << SDL_GetAudioDeviceName(i, 0) << '\n';
    }
    cout << endl;

    setActiveDevice(0);

    cout << "SDL initialized" << endl;

    mainLoop();

    SDL_Quit();
    return 0;
}

void mainLoop() {
    SDL_Event event;
    while (running) {
        calculateDeltaTime(true);

        //Handle quit events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                cout << "User quit the test" << endl;
            } else if (event.type == SDL_KEYDOWN && !autoMode) {
                if (event.key.keysym.sym == SDLK_LEFT && !leftPressed) {
                    leftPressed = true;
                    devIndex--;
                    if (devIndex < 0) devIndex = SDL_GetNumAudioDevices(0) - 1;

                    setActiveDevice(devIndex);
                }
                if (event.key.keysym.sym == SDLK_RIGHT && !rightPressed) {
                    rightPressed = true;
                    devIndex++;
                    if (devIndex == SDL_GetNumAudioDevices(0)) devIndex = 0;

                    setActiveDevice(devIndex);
                }
            } else if (event.type == SDL_KEYUP && !autoMode) {
                if (event.key.keysym.sym == SDLK_LEFT) leftPressed = false;
                if (event.key.keysym.sym == SDLK_RIGHT) rightPressed = false;
            }
        }

        //Loop
        angle += deltaTime * 90;
        if (angle > 360.0) angle -= 360.0;
        totalTime += deltaTime;
        if (autoMode && totalTime >= nextTime) {
            nextTime += 4.0;
            devIndex++;
            if (devIndex == SDL_GetNumAudioDevices(0)) {
                cout << "All devices tested. Stopping" << endl;
                break;
            } else {
                cout << "Changing device\n";
                setActiveDevice(devIndex);
            }
        }

        calculateVolumes();


        //Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 102, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopyEx(renderer, speakerTex, NULL, &speakerPos, angle, NULL, SDL_FLIP_NONE);

        drawVolumes();

        SDL_RenderPresent(renderer);

        calculateDeltaTime(false);
    }
}

void calculateDeltaTime(const bool& startFrame) {
    if (startFrame) {
        start = system_clock::now();
    } else {
        endTime = system_clock::now();
        d = endTime - start;
        deltaTime = d.count();
    }
}

void printDevSpecs() {
    cout << "Device Specs: " << devName << endl;
    cout << (int) dev.channels << " Channels ";
    unsigned char index = (dev.channels > 0 && dev.channels < 9) ? dev.channels : 0;
    cout << modeNames.at(index) << endl;
    
    dev.freq = freqMax;
    dev.format = AUDIO_S16SYS;
    dev.samples = 4096;
    dev.callback = fillBuffer;
}

void drawVolumes() {
    for (int channel = FL; channel <= BC; channel++) {
        //If channel is not present in channel mode or the angle is -1 (i.e. the Subwoofer), it is skipped
        if (channelConfigs.at(dev.channels).at(channel) == -1 || channelAngles.at(channel) == -1.0) continue;

        const SDL_Rect& r = channelPositions.at(channel);
        
        //Draw frame
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &r);

        //Draw volume
        volume.x = r.x + 1;
        int v = channelVolumes.at(channel) * 148;
        volume.y = r.y + 149 - v;
        volume.h = v;
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &volume);
    }
}

void calculateVolumes() {
    for (int channel = FL; channel <= BC; channel++) {
        if (channelConfigs.at(dev.channels).at(channel) == -1 || channelAngles.at(channel) == -1.0) continue;
        
        //calculate the differences from both sides of the circle and use the smaller one
        double diff = abs(angle - channelAngles.at(channel));
        double otherDiff = 360.0 - diff;
        double smallerDiff = (diff < otherDiff) ? diff : otherDiff;

        //The bigger the difference, the quieter the channel
        channelVolumes.at(channel) = 1.0 - (smallerDiff / 180.0);
    }
}

bool setActiveDevice(const int& index) {
    SDL_CloseAudioDevice(openDevice);

    devName = SDL_GetAudioDeviceName(index, 0);
    if (SDL_GetAudioDeviceSpec(index, 0, &dev)) {
        cerr << "Couldn't get info for device " << index << ": " << SDL_GetError() << '\n';
        return false;
    }

    printDevSpecs();

    openDevice = SDL_OpenAudioDevice(devName.c_str(), 0, &dev, NULL, 0);
    if (!openDevice) {
        cerr << "Couldn't open device " << index << ": " << SDL_GetError() <<'\n';
        return false;
    }

    SDL_PauseAudioDevice(openDevice, 0);

    return true;
}

void fillBuffer(void* userdata, Uint8* stream, int len) {
    Sint16* buffer = (Sint16*) stream;
    int samples = len / sizeof(Sint16);

    SDL_memset(stream, 0, len);

    for (int i = 0; i < samples; i += dev.channels) {
        double time = (double) totalSamples / freqMax;
        double val = SDL_sin(twoPi * time * 440) * 0.5 * SDL_MAX_SINT16; //Normal value (half of maximal amplitude)

        for (int channel = FL; channel <= BC; channel++) {
            int channelIndex = channelConfigs.at(dev.channels).at(channel);
            if (channelIndex == -1 || channelAngles.at(channel) == -1.0) continue;

            buffer[i + channelIndex] = (Sint16)(channelVolumes.at(channel) * val);
        }
        totalSamples++;
    }
}