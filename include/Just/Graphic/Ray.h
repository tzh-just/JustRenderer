#pragma once

#include "Just/Math/Vector.h"

namespace Just {
    template<size_t N, typename T>
    struct Ray {
        Vector<N, T> origin;
        Vector<N, T> direction;

        Ray() : origin(0), direction(0) {}

        Ray(const Vector<N, T> &orig, const Vector<N, T> &dir) : origin(orig), direction(dir) {}

        Vector<N, T> At(T time) const {
            return origin + direction * time;
        }
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    template<size_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Ray<N, T> &ray) {
        return os << "-----------------------------------------------" << std::endl
                  << "origin    = " << ray.origin << std::endl
                  << "direction = " << ray.direction << std::endl;
    }

    using Ray3f = Ray<3, float>;
}
