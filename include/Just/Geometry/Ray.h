#pragma once

#include "Just/Math/Vector.h"

namespace Just {
    template<size_t N, typename T>
    struct Ray {
        Vector<N, T> origin;
        Vector<N, T> direction;

        Ray(const Vector<N, T> &orig, const Vector<N, T> &dir) : origin(orig), direction(dir) {}

        Vector<N, T> At(T time) const {
            return origin + direction * time;
        }
    };

    using Ray3f = Ray<3, float>;
}
