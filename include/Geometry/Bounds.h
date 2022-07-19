//================================================
// 边界模板
//================================================

#pragma once

#include "Math/Vector.h"
#include "Graphics/Object.h"
#include "Ray.h"

namespace Just {
    template<size_t N, typename T>
    struct Bounds : Object{
        Vector<N, T> min;
        Vector<N, T> max;

        Bounds(const Vector<N, T> &min_, const Vector<N, T> &max_) : min(min_), max(max_) {}

        HitRecord Intersect(Ray3f &ray) override {
            HitRecord record;
            return record;
        }
    };

}