#include <iostream>
#include <chrono>
#include "SDL.h"
#include "UI/ImageHandler/ImageHandler.hpp"

using namespace std;
using namespace chrono;

//Global variables
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* speakerTex;
SDL_Rect speakerPos {0, 0, 600, 600};
bool running = true;
double deltaTime = 0.0, angle = 0.0;
time_point<system_clock> start, endTime;
duration<double> d;

//Functions
int mainLoop();
void fillBuffer(void* userdata, Uint8* stream, int len);
void calculateDeltaTime(const bool& startFrame);

int main() {
    cout << "Starting surround test" << endl;

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

    cout << "SDL initialized" << endl;

    int ret = mainLoop();

    SDL_Quit();
    return ret;
}

int mainLoop() {
    SDL_Event event;
    int ret = 0;
    while (running) {
        calculateDeltaTime(true);

        //Handle quit events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                cout << "User quit the test" << endl;
            }
        }

        //Loop here
        angle += deltaTime * 90;
        if (angle > 360.0) angle -= 360.0;


        //Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 102, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopyEx(renderer, speakerTex, NULL, &speakerPos, angle, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);

        calculateDeltaTime(false);
    }

    return ret;
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