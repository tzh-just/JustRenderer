#pragma once

#include "Global.h"

namespace Just {
    template<typename T>
    struct Array3 {
        T x, y, z;

        Array3() : x(T()), y(T()), z(T()) {}

        explicit Array3(T val) : x(val), y(val), z(val) {}

        Array3(T x, T y, T z) : x(x), y(y), z(z) {}

        T& operator[](size_t i) {
            assert(i < 3);
            return (&x)[i];
        }

        T operator[](size_t i) const {
            assert(i < 3);
            return (&x)[i];
        }
    };

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Array3<T>& a) {
        return os << "[" << a.x << "," << a.y << "," << a.z << "]";
    }

    using Array3f = Array3<float>;
    using Array3i = Array3<int>;
}