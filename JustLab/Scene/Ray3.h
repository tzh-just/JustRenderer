//================================================
// 射线
//================================================

#pragma once

#include <Math/Vector3.h>

namespace just
{
    template<typename T>
    struct Ray3
    {
        using Vector = Vector3<T>;
        using Ray = Ray3<T>;

        Vector origin, direction;

        T time;

        constexpr Ray3() : origin(), direction(), time(0) {}

        constexpr Ray3(const Vector& orig, const Vector& dir) : origin(orig), direction(dir), time(0) {}

        friend std::ostream& operator<<(std::ostream& os, const Ray& ray)
        {
            return os << "origin    = " << ray.origin << ", " << "direction = " << ray.direction;
        }
    };

    using Ray3f = Ray3<float>;

}
