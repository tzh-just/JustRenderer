#pragma once

#include <vector>
#include "Global.h"
#include "Emitter/Emitter.h"
#include "Mesh.h"

namespace Just{
    struct Scene{
        std::vector<std::shared_ptr<TriangleMesh>> meshes;
        std::vector<std::shared_ptr<Emitter>> emitters;
    };
}
