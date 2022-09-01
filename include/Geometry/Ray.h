#pragma once

#include "Math/Vector.h"
#include "Math/Vector.h"

namespace Just {
    template<size_t N, typename T>
    struct Ray {
        Point <N, T> origin;
        Vector<N, T> direction;
        mutable float tMax;

        Ray() : tMax(kFloatMax) {}

        Ray(const Point <N, T>& origin, const Vector<N, T>& direction) :
                origin(origin), direction(direction), tMax(kFloatMax) {}

        Point <N, T> At(float t) const {
            return origin + direction * t;
        }
    };

    using Ray3f = Ray<3, float>;
}
