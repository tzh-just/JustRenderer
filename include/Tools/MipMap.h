#pragma once

#include <vector>

#include "Texture.h"

namespace Just {
    struct MipMap {
    public:
        int level;
        Texture* source;
        std::vector<Texture> mipmap;

        MipMap(Texture* source, int level) : source(source), level(level){

        }
    };
}
