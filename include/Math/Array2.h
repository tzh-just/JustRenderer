#pragma once

#include "Global.h"

namespace Just {
    template<typename T>
    struct Array2 {
        T x, y;

        Array2() : x(T()), y(T()) {}

        explicit Array2(T val) : x(val), y(val){}

        Array2(T x, T y) : x(x), y(y) {}

        T& operator[](size_t i) {
            assert(i < 2);
            return (&x)[i];
        }

        T operator[](size_t i) const {
            assert(i < 2);
            return (&x)[i];
        }
    };

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Array2<T>& a) {
        return os << "[" << a.x << "," << a.y << "]";
    }

    using Array2f = Array2<float>;
    using Array2i = Array2<int>;
}