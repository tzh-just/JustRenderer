//================================================
// 边界模板
//================================================

#pragma once

#include "Vector.h"
#include "Ray.h"
#include "Hittable.h"

namespace Just {
    template<size_t N, typename T>
    struct Bounds : Hittable{
        Vector<N, T> min;
        Vector<N, T> max;

        Bounds(const Vector<N, T> &min_, const Vector<N, T> &max_) : min(min_), max(max_) {}

        HitRecord Intersect(const Ray3f &ray) override {
            HitRecord record;
            return record;
        }
    };

}