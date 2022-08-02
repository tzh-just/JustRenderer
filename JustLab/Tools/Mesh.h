//================================================
// 三维网格
//================================================

#pragma once

#include <vector>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Geometry/Bounds3.h>

namespace just
{
    struct Mesh
    {
        std::vector<Vector3i> faces;
        std::vector<Vector3f> positions;
        std::vector<Vector3f> normals;
        std::vector<Vector2f> uvs;
        Bounds3f bbox;
        
        Bounds3f GetFaceBBox(size_t face_index);
        bool Intersect(size_t face_index, Ray3f* ray) const;
    };

    Bounds3f Mesh::GetFaceBBox(size_t face_index)
    {
        Bounds3f bbox_face;
        //查询指定三角面的顶点索引
        auto& face = faces[face_index];
        for (int i = 0; i < 3; ++i)
        {
            //遍历三角面的顶点确定其包围盒
            auto& point = positions[face[i]];
            bbox_face.ExpandBy(point);
        }
        return bbox_face;
    }

    bool Mesh::Intersect(size_t face_index, Ray3f* ray) const
    {
        auto& face = faces[face_index];
        Vector3f edge1 = positions[face.y] - positions[face.x];
        Vector3f edge2 = positions[face.z] - positions[face.y];

        return false;
    }

}