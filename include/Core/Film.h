#pragma once

#include <vector>
#include "Math/Vector3.h"
#include "Math/Point2.h"
#include "Math/Color3.h"
#include "Math/Color4.h"
#include "Geometry/Bounds.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace Just {

enum class ImageType{
    PNG,
    TGA,
};

struct Film {
    std::vector<RGB> frameBuffer;

    Bounds2i bounds;

    Point2i resolution;

    explicit Film(const Point2i& resolution) : resolution(resolution) {}

    bool StoreImage(const std::string& fileName, ImageType type) const;
};

bool Film::StoreImage(const std::string& fileName, ImageType type) const {
    if(type == ImageType::PNG) {
        return stbi_write_png(fileName.c_str(), resolution.x, resolution.y, 3, frameBuffer.data(), 0);
    }
    else if(type==ImageType::TGA) {
        return stbi_write_tga(fileName.c_str(), resolution.x, resolution.y, 3, frameBuffer.data());
    }
    else {
        return false;
    }
}

}