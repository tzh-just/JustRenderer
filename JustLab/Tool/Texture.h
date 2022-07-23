//================================================
// 纹理
//================================================

#pragma once

#include <memory>
#include "Image.h"

namespace Just{
    class Texture{
    private:
        std::shared_ptr<Image> image;
    };
}