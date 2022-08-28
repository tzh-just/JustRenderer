#pragma once

#include "Math/Color3.h"
#include "Math/Array2.h"

namespace Just {
    struct Image{

    };
    struct Texture {
    public:
        int width, height;

        Color3f Sample();
    };
}
