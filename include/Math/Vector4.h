#pragma once

#include "Global.h"
#include "Point3.h"

namespace Just {
    template<typename T>
    struct Vector4 {
        T x, y, z, w;

        Vector4()  : x(T()), y(T()), z(T()), w(T()) {}

        explicit Vector4(T val) : x(val), y(val), z(val), w(val) {}

        Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

        T& operator[](size_t i) {
            assert(i < 4);
            return (&x)[i];
        }

        T operator[](size_t i) const {
            assert(i < 4);
            return (&x)[i];
        }
    };

    //点乘
    template<typename T>
    inline T Dot(const Vector4<T>& v1, const Vector4<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Vector4<T>& v) {
        return os << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    }

    using Vector4f = Vector4<float>;
}