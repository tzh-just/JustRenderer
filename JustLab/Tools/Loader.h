#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Math/Array3.h"
#include "Math/Array2.h"
#include "Math/Vector3.h"
#include "Shape/TriangleMesh.h"

namespace Just {
    class Loader {
    public:
        static void LoadMesh(TriangleMesh* mesh, const std::string& filePath);
        static void LoadTexture(Texture* mesh, const std::string& filePath);
    };
}