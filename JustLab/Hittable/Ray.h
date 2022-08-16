//================================================
// 射线
//================================================

#pragma once

#include "Math/Vector.h"
#include "Math/Point.h"

namespace Just
{
    template<size_t N, typename T>
    struct Ray
    {
        Point<N, T> origin;
        Vector<N, T> direction;
        union
        {
            T hitTime;
            T distance;
        };

        constexpr Ray() : origin(), direction(), hitTime(0) {}

        constexpr Ray(const Point<N, T>& origin, const Vector<N, T>& direction) : origin(origin), direction(direction), hitTime(0) {}
    };

    template<size_t N, typename T>
    std::ostream& operator<<(std::ostream& os, const Ray<N, T>& ray)
    {
        return os << "origin    = " << ray.origin << ", " << "direction = " << ray.direction;
    }

    using Ray3f = Ray<3, float>;

}
