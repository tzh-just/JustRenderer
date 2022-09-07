#pragma once

#include "Global.h"

namespace Just {
template<typename T>
struct Point2 {
    T x, y;

    //构造函数
    Point2() : x(T()), y(T()) {}

    explicit Point2(T val) : x(val), y(val) {
        assert(!HasNaNs());
    }

    explicit Point2(const Point3<T>& p) : x(p.x), y(p.y) {
        assert(!HasNaNs());
    }

    Point2(T x, T y) : x(x), y(y) {
        assert(!HasNaNs());
    }

    //合法性判断
    bool HasNaNs() const {
        return std::isnan(x) || std::isnan(y);
    }

    //索引操作符重载
    T& operator[](size_t i) {
        assert(i < 2);
        return (&x)[i];
    }

    T operator[](size_t i) const {
        assert(i < 2);
        return (&x)[i];
    }
};

//p=-a
template<typename T>
Point2<T> operator-(const Point2<T>& p) {
    return {-p.x, -p.y};
}

//p=a+b
template<typename T>
Point2<T> operator+(const Point2<T>& p1, const Point2<T>& p2) {
    return {p1.x + p2.x, p1.y + p2.y};
}

//p=a-b
template<typename T>
Vector3<T> operator-(const Point2<T>& p1, const Point2<T>& p2) {
    return {p1.x - p2.x, p1.y - p2.y};
}

//p=a*b
template<typename T>
Point2<T> operator*(const Point2<T>& p1, const Point2<T>& p2) {
    return {p1.x * p2.x, p1.y * p2.y};
}

//a+=b
template<typename T>
Point2<T>& operator+=(Point2<T>& p1, const Point2<T>& p2) {
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

//a-=b
template<typename T>
Point2<T>& operator-=(Point2<T>& p1, const Point2<T>& p2) {
    p1.x -= p2.x;
    p1.y -= p2.y;
    return p1;
}

//a*=b
template<typename T>
Point2<T>& operator*=(Point2<T>& p1, const Point2<T>& p2) {
    p1.x *= p2.x;
    p1.y *= p2.y;
    return p1;
}

//a*=k
template<typename T, typename U>
Point2<T>& operator*=(Point2<T>& p, U k) {
    p.x *= k;
    p.y *= k;
    return p;
}

//a/=k
template<typename T, typename U>
Point2<T>& operator/=(Point2<T>& p, U k) {
    assert(k != 0);
    p.x /= k;
    p.y /= k;
    return p;
}

//p=a*k
template<typename T, typename U>
Point2<T> operator*(const Point2<T>& p, U k) {
    return {p.x * k, p.y * k};
}

//p=k*a
template<typename T, typename U>
Point2<T> operator*(U k, const Point2<T>& p) {
    return {p.x * k, p.y * k};
}

//p=a/k
template<typename T, typename U>
Point2<T> operator/(const Point2<T>& p, U k) {
    assert(k != 0);
    return {p.x / k, p.y / k};
}

//p=a==b
template<typename T>
bool operator==(const Point2<T>& p1, const Point2<T>& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

//p=a!=b
template<typename T>
bool operator!=(const Point2<T>& p1, const Point2<T>& p2) {
    return p1.x != p2.x || p1.y != p2.y;
}

//p=a<b
template<typename T>
bool operator<(const Point2<T>& p1, const Point2<T>& p2) {
    return p1.x < p2.x && p1.y < p2.y;
}

//p=a<=b
template<typename T>
bool operator<=(const Point2<T>& p1, const Point2<T>& p2) {
    return p1.x <= p2.x && p1.y <= p2.y;
}

//p=a>b
template<typename T>
bool operator>(const Point2<T>& p1, const Point2<T>& p2) {
    return p1.x > p2.x && p1.y > p2.y;
}

//p=a>=b
template<typename T>
bool operator>=(const Point2<T>& p1, const Point2<T>& p2) {
    return p1.x >= p2.x && p1.y >= p2.y;
}

//ostream输出
template<typename T>
std::ostream& operator<<(std::ostream& os, const Point2<T>& p) {
    os << "[ " << p.x << ", " << p.y << " ]";
    return os;
}

//Distance距离
template<typename T>
T Distance(const Point2<T>& p1, const Point2<T>& p2) {
    return (p1 - p2).Length();
}

//DistanceSquared
template<typename T>
T DistanceSquared(const Point2<T>& p1, const Point2<T>& p2) {
    return (p1 - p2).LengthSquared();
}

//Lerp插值
template<typename T>
Point2<T> Lerp(const Point2<T>& p1, const Point2<T>& p2, T t) {
    return (1 - t) * p1 + t * p2;
}

//Min
template<typename T>
Point2<T> Min(const Point2<T>& p1, const Point2<T>& p2) {
    return {std::min(p1.x, p2.x), std::min(p1.y, p2.y)};
}

//Max
template<typename T>
Point2<T> Max(const Point2<T>& p1, const Point2<T>& p2) {
    return {std::max(p1.x, p2.x), std::max(p1.y, p2.y)};
}

//Floor
template<typename T>
Point2<T> Floor(const Point2<T>& p) {
    return {std::floor(p.x), std::floor(p.y)};
}

//Ceil
template<typename T>
Point2<T> Ceil(const Point2<T>& p) {
    return {std::ceil(p.x), std::ceil(p.y)};
}

//Abs
template<typename T>
Point2<T> Abs(const Point2<T>& p) {
    return {std::abs(p.x), std::abs(p.y)};
}

using Point2f = Point2<float>;
using Point2i = Point2<int>;
}