#pragma once

#include <vector>
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
        Bounds2f bbox;
    public:

    };
}