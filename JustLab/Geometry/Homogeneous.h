#pragma once

#include "Global.h"
#include "Vector3.h"
#include "Point3.h"

namespace Just {
    template<typename T>
    struct Homogeneous {
        T x, y, z, w;

        Homogeneous() { x = y = z = w = 0; }

        Homogeneous(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

        bool HasNaNs() const {
            return std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(w);
        }

        T& operator[](int i) {
            assert(i <= 3 && i >= 0);
            return (&x)[i];
        }

        T operator[](int i) const {
            assert(i <= 3 && i >= 0);
            return (&x)[i];
        }
    };

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Homogeneous<T>& h) {
        return os << "(" << h.x << "," << h.y << "," << h.z << "," << h.w << ")";
    }
}