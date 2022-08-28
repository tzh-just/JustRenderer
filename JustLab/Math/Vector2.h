#pragma once

#include "Global.h"

namespace Just {
    template<typename T>
    struct Vector2 {
        T x, y;

        Vector2()  : x(T()), y(T()) {}

        Vector2(T x, T y) : x(T()), y(T()) {}

        T& operator[](size_t i) {
            assert(i < 2);
            return (&x)[i];
        }

        T operator[](size_t i) const {
            assert(i < 2);
            return (&x)[i];
        }
    };

    template<typename T>
    inline Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2) {
        return Vector2<T>(v1.x + v2.x, v1.y + v2.y);
    }

    template<typename T>
    inline Vector2<T>& operator+=(Vector2<T>& v1, const Vector2<T>& v2) {
        v1.x += v2.x;
        v1.y += v2.y;
        return v1;
    }

    template<typename T>
    inline Vector2<T> operator-(Vector2<T>& v1, const Vector2<T>& v2) {
        return Vector2<T>(v1.x - v2.x, v1.y - v2.y);
    }

    template<typename T>
    inline Vector2<T>& operator-=(Vector2<T>& v1, const Vector2<T>& v2) {
        v1.x -= v2.x;
        v1.y -= v2.y;
        return v1;
    }

    template<typename T>
    inline Vector2<T> operator*(Vector2<T>& v, T k) {
        return Vector2<T>(v.x * k, v.y * k);
    }

    template<typename T>
    inline Vector2<T> operator*(T k, const Vector2<T>& v) {
        return v * k;
    }

    template<typename T>
    inline Vector2<T>& operator*=(Vector2<T>& v, T k) {
        assert(!std::isnan(k));
        v.x *= k;
        v.y *= k;
        return v;
    }

    //向量除法
    template<typename T>
    inline Vector2<T> operator/(Vector2<T>& v, T k) {
        assert(k != 0);
        float inv = (float) 1 / k;
        return Vector2<T>(v.x * inv, v.y * inv);
    }

    template<typename T>
    inline Vector2<T>& operator/=(Vector2<T>& v, T k) {
        assert(k != 0);
        float inv = (float) 1 / k;
        v.x *= inv;
        v.y *= inv;
        return v;
    }

    //向量取反
    template<typename T>
    inline Vector2<T> operator-(Vector2<T>& v) {
        return Vector2<T>(-v.x, -v.y);
    }

    //向量点乘
    template<typename T>
    inline T Dot(const Vector2<T>& v1, const Vector2<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
        return os << "<" << v.x << "," << v.y << ">";
    }

    using Vector2f = Vector2<float>;
}