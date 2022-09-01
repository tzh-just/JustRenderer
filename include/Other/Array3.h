#pragma once

#include "Global.h"

namespace Just {
    template<typename T>
    struct Tuple3 {
        T x, y, z;

        Tuple3() : x(T()), y(T()), z(T()) {}

        explicit Tuple3(T val) : x(val), y(val), z(val) {}

        Tuple3(T x, T y, T z) : x(x), y(y), z(z) {}

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
    inline std::ostream& operator<<(std::ostream& os, const Tuple3<T>& a) {
        return os << "[" << a.x << "," << a.y << "," << a.z << "]";
    }

    using Tuple3f = Tuple3<float>;
    using Tuple3i = Tuple3<int>;
}