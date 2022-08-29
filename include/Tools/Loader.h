#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Math/Array3.h"
#include "Math/Array2.h"
#include "Math/Vector3.h"
#include "Shape/TriangleMesh.h"
#include "Tools/Texture.h"

namespace Just {
    class Loader {
    public:
        static void LoadTexture(Texture* texture, const std::string& filePath);

        static void LoadMesh(TriangleMesh* mesh, const std::string& filePath);
    };
}