//================================================
// 射线
//================================================

#pragma once

#include "Math/Vector3.h"

namespace just
{
    template<typename T>
    struct Ray3
    {
        using Vector = Vector3<T>;
        using Ray = Ray3<T>;

        Vector origin, direction;

        union{
            T hitTime;
            T distance;
        };


        constexpr Ray3() : origin(), direction(), hitTime(0) {}

        constexpr Ray3(const Vector& origin, const Vector& direction) : origin(origin), direction(direction), hitTime(0) {}

        friend std::ostream& operator<<(std::ostream& os, const Ray& ray)
        {
            return os << "origin    = " << ray.origin << ", " << "direction = " << ray.direction;
        }
    };

    using Ray3f = Ray3<float>;

}
