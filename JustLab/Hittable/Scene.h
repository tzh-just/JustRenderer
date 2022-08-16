//================================================
// 射线
//================================================

#pragma once

#include <vector>
#include "Global.h"
#include "Emitter/Emitter.h"
#include "Mesh.h"

namespace Just{
    struct Scene{
        std::vector<std::shared_ptr<Mesh>> meshes;
        std::vector<std::shared_ptr<Emitter>> emitters;
    };
}
