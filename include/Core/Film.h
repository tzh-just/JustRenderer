#pragma once

#include <vector>
#include <Math/Point2.h>
#include <Geometry/Bounds2.h>
#include <Math/Color3.h>

namespace Just {
    struct Pixel {
        RGB rgb;
        float weight;

        Pixel() : rgb(), weight(0) {}
    };

    class Film {
    private:
        std::vector<Pixel> pixels;
        Bounds2i bbox;
    public:
        Point2i resolution;

        explicit Film(const Point2i& resolution) : resolution(resolution) {}

        bool StoreImage() const;
    };
}