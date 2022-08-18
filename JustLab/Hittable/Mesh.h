#pragma once

#include <vector>
#include "Geometry/Vector3.h"
#include "Geometry/Point2.h"
#include "Geometry/Bounds3.h"

namespace Just {
    struct Mesh {
        std::vector<Point3i> faces;
        std::vector<Point3f> positions;
        std::vector<Vector3f> normals;
        std::vector<Point2f> uvs;

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
        auto& face = faces[faceIndex];
        Vector3f edge1 = positions[face.y] - positions[face.x];
        Vector3f edge2 = positions[face.z] - positions[face.y];
        return false;
    }

}