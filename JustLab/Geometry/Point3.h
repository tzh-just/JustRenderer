#pragma once

#include "Global.h"
#include "Vector3.h"

namespace Just {
    template<typename T>
    struct Point3 {
        T x, y, z;

        Point3() {
            x = y = z = 0;
        }

        Point3(T x, T y, T z) : x(x), y(y), z(z) {
            assert(!HasNaNs);
        }

        template<typename U>
        explicit Point3(const Point3<U>& p) : x(p.x), y(p.y), z(p.z) {
            assert(!HasNaNs);
        }

        bool HasNaNs() const {
            return std::isnan(x) || std::isnan(y) || std::isnan(z);
        }

        T& operator[](int i) {
            assert(i <= 2 && i >= 0);
            return (&x)[i];
        }

        T operator[](int i) const {
            assert(i <= 2 && i >= 0);
            return (&x)[i];
        }
    };

    template<typename T>
    Point3<T> operator+(const Point3<T>& p1, const Point3<T>& p2) const {
        return Point3<T>(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
    }

    template<typename T>
    Point3<T>& operator+=(Point3<T>& p1, const Point3<T>& p2) {
        p1.x += p2.x;
        p1.y += p2.y;
        p1.z += p2.z;
        return p1;
    }

    template<typename T>
    Point3<T> operator+(const Point3<T>& p, const Vector3<T>& v) const {
        return Point3<T>(p.x + v.x, p.y + v.y, p.z + v.z);
    }

    template<typename T>
    Point3<T>& operator+=(Point3<T>& p, const Vector3<T>& v) {
        p.x += v.x;
        p.y += v.y;
        p.z += v.z;
        return p;
    }

    template<typename T>
    Vector3<T> operator-(const Point3<T>& p1, const Point3<T>& p2) const {
        return Vector3<T>(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
    }

    template<typename T>
    Point3<T> operator-(const Point3<T>& p, const Vector3<T>& v) const {
        return Point3<T>(p.x - v.x, p.y - v.y, p.z - v.z);
    }

    template<typename T>
    Point3<T> operator*(const Point3<T>& p, T k) const {
        return Point3<T>(p.x * k, p.y * k, p.z * k);
    }

    template<typename T>
    Point3<T>& operator*=(Point3<T>& p, T k) {
        assert(!std::isnan(k));
        p.x *= k;
        p.y *= k;
        p.z *= k;
        return p;
    }

    template<typename T>
    Point3<T> operator*(T k, const Point3<T>& p) {
        return p * k;
    }

    template<typename T>
    Point3<T> operator/(const Point3<T>& p, T k) const {
        assert(k != 0);
        float inv = (float) 1 / k;
        return Point3<T>(p.x * inv, p.y * inv, p.z * inv);
    }

    template<typename T>
    Point3<T>& operator/=(Point3<T>& p, T k) {
        assert(k != 0);
        float inv = (float) 1 / k;
        p.x *= inv;
        p.y *= inv;
        p.z *= inv;
        return p;
    }

    //取反
    template<typename T>
    Point3<T> operator-(const Point3<T>& p) const {
        return Point3<T>(-p.x, -p.y, -p.z);
    }

    //点乘
    template<typename T>
    inline T Dot(const Point3<T>& v1, const Point3<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    //距离
    template<typename T>
    inline T Distance(const Point3<T>& p1, const Point3<T>& p2) {
        return (p1 - p2).Length();
    }

    template<typename T>
    inline T DistanceSquared(const Point3<T>& p1, const Point3<T>& p2) {
        return (p1 - p2).LengthSquared();
    }

    //线性插值
    template<typename T>
    inline Point3<T> Lerp(float t, const Point3<T>& p1, const Point3<T>& p2) {
        return (1 - t) * p1 + t * p2;
    }

    //各维度最小值
    template<typename T>
    inline Point3<T> Min(const Point3<T>& p1, const Point3<T>& p2) {
        return Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z));
    }

    //各维度最大值
    template<typename T>
    inline Point3<T> Max(const Point3<T>& p1, const Point3<T>& p2) {
        return Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z));
    }

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Point3<T>& p) {
        return os << "(" << p.x << "," << p.y << "," << p.z << ")";
    }

    using Point3i = Point3<int>;
    using Point3f = Point3<float>;
}