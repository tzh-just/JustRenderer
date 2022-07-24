//================================================
// 射线模板
//================================================

#pragma once

#include "Math/Vector.h"

namespace Just {
    template<uint32_t N, typename T>
    struct Ray {
        Vector<N, T> origin;
        Vector<N, T> direction;

        float time;

        Ray() : origin(), direction(), time() {}

        Ray(const Vector<N, T> &orig, const Vector<N, T> &dir) : origin(orig), direction(dir), time() {}

        Vector<N, T> At(T t) {
            time = t;
            return origin + direction * time;
        }
    };

    template<uint32_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Ray<N, T> &ray) {
        return os << "origin    = " << ray.origin << ", " << "direction = " << ray.direction;
    }

    using Ray3f = Ray<3, float>;
}
