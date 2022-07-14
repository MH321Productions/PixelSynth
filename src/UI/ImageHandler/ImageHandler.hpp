#ifndef PS_UI_IMAGE_HANDLER_HPP
#define PS_UI_IMAGE_HANDLER_HPP

#include <map>

class wxImage;

enum class ImageType {
    SineWave, SquareWave, TriangleWave, SawWave, NoiseWave,
    SineWaveSelected, SquareWaveSelected, TriangleWaveSelected, SawWaveSelected, NoiseWaveSelected
};

struct ImageData {
    unsigned char* data;
    unsigned int size;
};

class ImageHandler {
    private:
        static const std::map<ImageType, ImageData> data;

    public:
        static wxImage loadImage(ImageType type);
};

#endif//PS_UI_IMAGE_HANDLER_HPP