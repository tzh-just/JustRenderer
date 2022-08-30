#pragma once

#include <vector>

#include "Math/Vector3.h"
#include "Math/Array2.h"
#include "Math/Array3.h"
#include "Geometry/Bounds3.h"

namespace Just {
    struct Face{
        std::vector<int> positionIndexes;
        std::vector<int> uvIndexes;
        std::vector<int> normalIndexes;
    };
    struct Mesh {
        std::vector<Vector3f> positions;
        std::vector<Face> faces;
        std::vector<Array2f> uvs;
        std::vector<Vector3f> normals;

        Bounds3f bbox;

        Bounds3f GetFaceBBox(size_t faceIndex);

        bool Intersect(size_t faceIndex, Ray* ray) const;
    };

    Bounds3f Mesh::GetFaceBBox(size_t faceIndex) {
        Bounds3f faceBBox;
        //查询指定三角面的顶点索引
        auto& face = faces[faceIndex];
        for (int i = 0; i < 3; ++i) {
            //遍历三角面的顶点确定其包围盒
            auto& point = positions[face[i]];
            Expand(faceBBox, point);
        }
        return faceBBox;
    }

    bool Mesh::Intersect(size_t faceIndex, Ray* ray) const {

    }
}