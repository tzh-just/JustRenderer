#pragma once

#include "Global.h"
#include "Math/Color3.h"

namespace Just {
    struct Image {
    };

    struct Texture {
        int width, height;
        std::vector<Spectrum> pixels;
    };
}
