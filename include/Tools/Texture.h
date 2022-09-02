#pragma once

#include "Math/Vector.h"

namespace Just {
    struct Image {
    };

    struct Texture {
        int width, height;
        std::vector<Color3i> pixels;
    };
}
