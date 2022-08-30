#pragma once

#include "Global.h"
#include "Vector2.h"

namespace Just {
    template<typename T>
    struct Point2 {
        T x, y;

        Point2() : x(T()), y(T()) {}

        explicit Point2(T val) : x(val), y(val) {}

        template<typename U>
        Point2(U x, U y) : x(x), y(y) {}

        T& operator[](size_t i) {
            assert(i < 2);
            return (&x)[i];
        }

        T operator[](size_t i) const {
            assert(i < 2);
            return (&x)[i];
        }
    };

    //加法
    template<typename T>
    Point2<T> operator+(const Point2<T>& p1, const Point2<T>& p2) {
        return Point2<T>(p1.x + p2.x, p1.y + p2.y);
    }

    //赋值加
    template<typename T>
    Point2<T>& operator+=(Point2<T>& p1, const Point2<T>& p2) {
        p1.x += p2.x;
        p1.y += p2.y;
        return p1;
    }

    //加法
    template<typename T>
    Point2<T> operator+(const Point2<T>& p, const Vector2<T>& v) {
        return Point2<T>(p.x + v.x, p.y + v.y);
    }

    //赋值加
    template<typename T>
    Point2<T>& operator+=(Point2<T>& p, const Vector2<T>& v) {
        p.x += v.x;
        p.y += v.y;
        return p;
    }

    //减法
    template<typename T>
    Vector2<T> operator-(const Point2<T>& p1, const Point2<T>& p2) {
        return Vector2<T>(p1.x - p2.x, p1.y - p2.y);
    }

    //赋值减
    template<typename T>
    Point2<T> operator-(const Point2<T>& p, const Vector2<T>& v) {
        return Point2<T>(p.x - v.x, p.y - v.y);
    }

    //后数乘
    template<typename T>
    Point2<T> operator*(const Point2<T>& p, T k) {
        return Point2<T>(p.x * k, p.y * k);
    }

    //前数乘
    template<typename T>
    Point2<T> operator*(T k, const Point2<T>& p) {
        return p * k;
    }

    //赋值数乘
    template<typename T>
    Point2<T>& operator*=(Point2<T>& p, T k) {
        assert(!std::isnan(k));
        p.x *= k;
        p.y *= k;
        return p;
    }

    //数除
    template<typename T>
    Point2<T> operator/(const Point2<T>& p, T k) {
        assert(k != 0);
        float inv = (float) 1 / k;
        return Point2<T>(p.x * inv, p.y * inv);
    }

    //赋值数除
    template<typename T>
    Point2<T>& operator/=(Point2<T>& p, T k) {
        assert(k != 0);
        float inv = (float) 1 / k;
        p.x *= inv;
        p.y *= inv;
        return p;
    }

    //取反
    template<typename T>
    Point2<T> operator-(const Point2<T>& p) {
        return Point2<T>(-p.x, -p.y);
    }

    //向量点乘
    template<typename T>
    inline T Dot(const Point2<T>& p1, const Point2<T>& p2) {
        return p1.x * p2.x + p1.y * p2.y;
    }

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Point2<T>& p) {
        return os << "(" << p.x << "," << p.y << ")";
    }

    using Point2i = Point2<int>;
    using Point2f = Point2<float>;
}