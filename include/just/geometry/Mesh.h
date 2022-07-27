//================================================
// 网格
//================================================

#pragma once

#include <vector>
#include "Hittable.h"
#include "Bounds.h"

namespace Just {
    //三角面顶点索引
    struct Face{
        Vector3f indices[3];
    };

    //网格
    class Mesh : Hittable {
    private:
        std::vector<Face> faces;
        std::vector<Vector3f> positions;
        std::vector<Vector3f> normals;
        std::vector<Vector2f> uvs;
        Bounds3f bbox;
    public:
        Mesh() : faces() {}

        HitRecord Intersect(Ray3f &ray) override {

        }
    };
}