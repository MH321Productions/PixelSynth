#ifndef PS_UI_IMAGE_HANDLER_HPP
#define PS_UI_IMAGE_HANDLER_HPP

#include <map>

class wxImage;
struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Surface;

enum class ImageType {
    SineWave, SquareWave, TriangleWave, SawWave, NoiseWave,
    SineWaveSelected, SquareWaveSelected, TriangleWaveSelected, SawWaveSelected, NoiseWaveSelected,
    SpeakerCircle
};

struct ImageData {
    unsigned char* data;
    unsigned int size;
};

class ImageHandler {
    private:
        static const std::map<ImageType, ImageData> data;

    public:
        #ifdef IH_USE_WX
        static wxImage loadImage(ImageType type);
        #endif

        #ifdef IH_USE_SDL
        static SDL_Surface* loadImage(ImageType type);
        static SDL_Texture* loadImage(ImageType type, SDL_Renderer* renderer);
        #endif
};

#endif//PS_UI_IMAGE_HANDLER_HPP