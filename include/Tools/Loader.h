#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Math/Tuple3.h"
#include "Math/Tuple2.h"
#include "Math/Vector.h"
#include "Shape/Mesh.h"
#include "Tools/Texture.h"

namespace Just {
    class Loader {
    public:
        static void LoadTexture(std::shared_ptr<Texture> texture, const std::string& filePath);

        static void LoadMesh(std::shared_ptr<Mesh> mesh, const std::string& filePath);
    };
}