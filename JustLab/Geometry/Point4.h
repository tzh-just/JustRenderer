#pragma once

#include "Global.h"
#include "Point3.h"

namespace Just {
    template<typename T>
    struct Point4 {
        T x, y, z, w;

        Point4() { x = y = z = w = 0; }

        Point4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

        explicit Point4(const Point3<T>& p) : x(p.x), y(p.y), z(p.z), w(1) {}

        T& operator[](int i) {
            assert(i <= 3 && i >= 0);
            return (&x)[i];
        }

        T operator[](int i) const {
            assert(i <= 3 && i >= 0);
            return (&x)[i];
        }
    };

    //点乘
    template<typename T>
    inline T Dot(const Point4<T>& p1, const Point4<T>& p2) {
        return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z + p1.w * p2.w;
    }

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Point4<T>& p) {
        return os << "(" << p.x << "," << p.y << "," << p.z << "," << p.w << ")";
    }

    using Point4f = Point4<float>;
}