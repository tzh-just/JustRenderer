//================================================
// 射线
//================================================

#pragma once

#include "Math/Vector.h"

namespace Just
{
    template<size_t N, typename T>
    struct Ray
    {
        using Vector = Vector<N, T>;

        Vector origin, direction;

        union
        {
            T hitTime;
            T distance;
        };


        constexpr Ray() : origin(), direction(), hitTime(0) {}

        constexpr Ray(const Vector& origin, const Vector& direction) : origin(origin), direction(direction), hitTime(0) {}

        friend std::ostream& operator<<(std::ostream& os, const Ray& ray)
        {
            return os << "origin    = " << ray.origin << ", " << "direction = " << ray.direction;
        }
    };

    using Ray3f = Ray<3, float>;

}
