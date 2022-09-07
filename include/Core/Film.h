#pragma once

#include <vector>
#include "Math/Vector3.h"
#include "Math/Point2.h"
#include "Math/Color3.h"
#include "Geometry/Bounds.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace Just {

struct Film {
    std::vector<uint8_t> pixels;

    Bounds2i bounds;

    Point2i resolution;

    explicit Film(const Point2i& resolution) : resolution(resolution) {
        pixels.reserve(resolution.x * resolution.y);
    }

    bool StoreImage(const std::string& fileName) const;
};

bool Film::StoreImage(const std::string& fileName) const {
    stbi_write_tga(fileName.c_str(), resolution.x, resolution.y, 3, pixels.data());
    return false;
}

}