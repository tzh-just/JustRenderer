//================================================
// 网格
//================================================

#pragma once

#include <vector>
#include "Hittable.h"
#include "Triangle.h"
#include "Bounds.h"

namespace Just {

    class Mesh : Hittable {
    private:
        std::vector<Triangle3f> triangles;
        Bounds3f bbox;
    public:
        Mesh() : triangles() {}

        HitRecord Intersect(Ray3f &ray) override {

        }
    };
}