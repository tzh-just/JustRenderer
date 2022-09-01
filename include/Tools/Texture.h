#pragma once

#include "Math/Color3.h"
#include "Math/Tuple2.h"

namespace Just {
    struct Image {
    };

    struct Texture {
        int width, height;
        std::vector<Color3i> pixels;
    };
}
