#pragma once

#include <vector>
#include "Math/Vector.h"
#include "Geometry/Bounds.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace Just {
struct Pixel {
    Color3i color;
    float weight;

    explicit Pixel(const Color3i& color) : color(color), weight(0) {}
};

struct Film {
    std::vector<Pixel> pixels;

    Bounds2i bounds;

    Point2i resolution;

    explicit Film(const Point2i& resolution) : resolution(resolution) {
        pixels.reserve(resolution.x * resolution.y);
    }

    bool StoreImage(const std::string& fileName) const;


    unsigned char* PixelsToData() const;
};

//RGB和光谱转换
static Spectrum RGB2Spectrum(const Color3i& rgb) {
    return {
            std::clamp(float(rgb.r) / 255.0f, 0.0f, 1.0f),
            std::clamp(float(rgb.g) / 255.0f, 0.0f, 1.0f),
            std::clamp(float(rgb.b) / 255.0f, 0.0f, 1.0f)
    };
}

static Color3i Spectrum2RGB(const Spectrum& spectrum) {
    return {
            std::clamp(int(spectrum.r * 255), 0, 255),
            std::clamp(int(spectrum.g * 255), 0, 255),
            std::clamp(int(spectrum.b * 255), 0, 255)
    };
}

bool Film::StoreImage(const std::string& fileName) const {
    stbi_write_tga(fileName.c_str(), resolution.x, resolution.y, 3, PixelsToData());
    return false;
}

unsigned char* Film::PixelsToData() const {
    int length = resolution.x * resolution.y * 3;
    auto* data = new unsigned char[length];
    for (int i = 0; i < resolution.x; ++i) {
        for (int j = 0; j < resolution.y; ++j) {
            for (int k = 0; k < 3; ++k) {
                data[i + resolution.x * j + k] = pixels[i + resolution.x * j].color[k];
            }
        }
    }
    return data;
}

}