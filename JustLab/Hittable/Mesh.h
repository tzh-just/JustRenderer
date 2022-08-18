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

        Bounds3f GetFaceBBox(int faceIndex);

        bool Intersect(int faceIndex, Ray* ray) const;
    };

    Bounds3f Mesh::GetFaceBBox(int faceIndex) {
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

    bool Mesh::Intersect(int faceIndex, Ray* ray) const {

    }

}