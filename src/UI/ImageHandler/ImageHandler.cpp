#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ImageHandler.hpp"
#include "Images.hpp"

#ifdef IH_USE_WX
#include <wx/image.h>
#endif //IH_USE_WX

#ifdef IH_USE_SDL
#include "SDL_render.h"
#include "SDL_surface.h"
#endif //IH_USE_SDL


using namespace std;

const map<ImageType, ImageData> ImageHandler::data = {
    {ImageType::SineWave,               {sine_png,              sine_png_len}},
    {ImageType::SquareWave,             {square_png,            square_png_len}},
    {ImageType::TriangleWave,           {triangle_png,          triangle_png_len}},
    {ImageType::SawWave,                {saw_png,               saw_png_len}},
    {ImageType::NoiseWave,              {noise_png,             noise_png_len}},
    {ImageType::SineWaveSelected,       {sineSelected_png,      sineSelected_png_len}},
    {ImageType::SquareWaveSelected,     {squareSelected_png,    squareSelected_png_len}},
    {ImageType::TriangleWaveSelected,   {triangleSelected_png,  triangleSelected_png_len}},
    {ImageType::SawWaveSelected,        {sawSelected_png,       sawSelected_png_len}},
    {ImageType::NoiseWaveSelected,      {noiseSelected_png,     noiseSelected_png_len}},
    {ImageType::SpeakerCircle,          {SpeakerCircle_png,     SpeakerCircle_png_len}}
};

#ifdef IH_USE_WX
wxImage ImageHandler::loadImage(ImageType type) {
    int width, height, channel;
    ImageData imData = data.at(type);
    uint8_t* img = stbi_load_from_memory(imData.data, imData.size, &width, &height, &channel, 4);
    if (!img) {
        cerr << "Couldn't load image" << endl;
        return {};
    }

    //split data in rgb and alpha
    uint8_t* rgb = new uint8_t[width * height * 3];
    uint8_t* alpha = new uint8_t[width * height];
    for (unsigned long i = 0; i < width * height; i++) {
        rgb[3 * i]     = img[4 * i];
        rgb[3 * i + 1] = img[4 * i + 1];
        rgb[3 * i + 2] = img[4 * i + 2];
        alpha[i]       = img[4 * i + 3];
    }

    stbi_image_free(img);

    return wxImage(width, height, rgb, alpha, false);
}
#endif

#ifdef IH_USE_SDL
SDL_Texture* ImageHandler::loadImage(ImageType type, SDL_Renderer* renderer) {
    SDL_Surface* surface = loadImage(type);
    SDL_Texture* tex = NULL;

    if (surface) {
        tex = SDL_CreateTextureFromSurface(renderer, surface);
        if (!tex) {
            cerr << "Couldn't create texture: " << SDL_GetError() << endl;
        }

        void* img = surface->pixels;
        SDL_FreeSurface(surface);
        stbi_image_free(img);
    }

    return tex;
}

SDL_Surface* ImageHandler::loadImage(ImageType type) {
    int width, height, channel;
    ImageData imData = data.at(type);
    uint8_t* img = stbi_load_from_memory(imData.data, imData.size, &width, &height, &channel, 4);
    if (!img) {
        cerr << "Couldn't load image" << endl;
        return {};
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(img, width, height, channel * 8, width * channel, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        cerr << "Couldn't create surface: " << SDL_GetError() << endl;
    }

    return surface;
}
#endif