//================================================
// 三维网格
//================================================

#pragma once

#include <vector>
#include "Math/Vector2.h"
#include "Math/Vector.h"
#include "Bounds.h"

namespace Just
{
    struct Mesh
    {
        std::vector<Vector3i> faces;
        std::vector<Vector3f> positions;
        std::vector<Vector3f> normals;
        std::vector<Vector2f> uvs;
        BoundingBox3f bbox;
        
        BoundingBox3f GetFaceBBox(size_t faceIndex);
        bool Intersect(size_t faceIndex, Ray3f* ray) const;
    };

    BoundingBox3f Mesh::GetFaceBBox(size_t faceIndex)
    {
        BoundingBox3f faceBBox;
        //查询指定三角面的顶点索引
        auto& face = faces[faceIndex];
        for (int i = 0; i < 3; ++i)
        {
            //遍历三角面的顶点确定其包围盒
            auto& point = positions[face[i]];
            faceBBox.ExpandBy(point);
        }
        return faceBBox;
    }

    bool Mesh::Intersect(size_t faceIndex, Ray3f* ray) const
    {
        auto& face = faces[faceIndex];
        Vector3f edge1 = positions[face.y] - positions[face.x];
        Vector3f edge2 = positions[face.z] - positions[face.y];

        return false;
    }

}