//================================================
// 边界模板
//================================================

#pragma once

#include "Math/Vector.h"
#include "Hittable.h"
#include "Ray.h"

namespace Just {
    template<size_t N, typename T>
    struct Bounds : Hittable {
        Vector<N, T> min;
        Vector<N, T> max;

        Bounds():min(),max(){}
        Bounds(const Vector<N, T> &min_, const Vector<N, T> &max_) : min(min_), max(max_) {}

        HitRecord Intersect(Ray3f &ray) override {
            HitRecord record;
            return record;
        }
    };

    using Bounds3f = Bounds<3, float>;

}