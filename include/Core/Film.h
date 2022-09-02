#pragma once

#include <vector>
#include "Math/Vector.h"
#include "Geometry/Bounds.h"

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

        explicit Film(const Point2i& resolution) : resolution(resolution) {}

        bool StoreImage() const;
    };

bool Film::StoreImage() const {
    return false;
}
}