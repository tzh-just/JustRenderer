#pragma once

#include <vector>

#include "Math/Vector3.h"
#include "Math/Array2.h"
#include "Math/Array3.h"

namespace Just {
    struct Face{
        std::vector<int> positionIndexes;
        std::vector<int> uvIndexes;
        std::vector<int> normalIndexes;
    };
    struct TriangleMesh {
        std::vector<Vector3f> positions;
        std::vector<Face> faces;
        std::vector<Array2f> uvs;
        std::vector<Vector3f> normals;
    };
}