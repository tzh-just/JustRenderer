#pragma once

#include <vector>
#include <Math/Point2.h>
#include <Geometry/Bounds2.h>
#include <Math/Color3.h>

namespace Just {
    struct Pixel {
        RGB color;
        float weight;

        explicit Pixel(const RGB& color) : color(color), weight(0) {}
    };

    struct Film {
        std::vector<Pixel> pixels;

        Bounds2i bounds;

        Point2i resolution;

        explicit Film(const Point2i& resolution) : resolution(resolution) {}

        bool StoreImage() const;
    };
}