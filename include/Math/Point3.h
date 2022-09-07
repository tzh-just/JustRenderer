#pragma once

#include "Global.h"

namespace Just {
template<typename T>
struct Point3 {
    T x, y, z;

    //构造函数
    Point3() : x(T()), y(T()), z(T()) {}

    explicit Point3(T val) : x(val), y(val), z(val) {}

    template<typename U>
    explicit Point3(const Point3<U>& p) : x(T(p.x)), y(T(p.y)), z(T(p.z)) {}

    Point3(T x, T y, T z) : x(x), y(y), z(z) {}

    //合法性判断
    bool HasNaNs() const {
        return std::isnan(x) || std::isnan(y) || std::isnan(z);
    }

    //索引操作符重载
    T& operator[](size_t i) {
        assert(i < 3);
        return (&x)[i];
    }

    T operator[](size_t i) const {
        assert(i < 3);
        return (&x)[i];
    }
};

//p=-a
template<typename T>
Point3<T> operator-(const Point3<T>& p) {
    return {-p.x, -p.y, -p.z};
}

//p=a+b
template<typename T>
Point3<T> operator+(const Point3<T>& p1, const Point3<T>& p2) {
    return {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}

//p+v
template<typename T>
Point3<T> operator+(const Point3<T>& p, const Vector3<T>& v) {
    return {p.x + v.x, p.y + v.y, p.z + v.z};
}

//p=a-b
template<typename T>
Vector3<T> operator-(const Point3<T>& p1, const Point3<T>& p2) {
    return {p1.x - p2.x, p1.y - p2.y , p1.z - p2.z};
}

//p-v
template<typename T>
Point3<T> operator-(const Point3<T>& p, const Vector3<T>& v) {
    return {p.x - v.x, p.y - v.y, p.z - v.z};
}

//p=a*b
template<typename T>
Point3<T> operator*(const Point3<T>& p1, const Point3<T>& p2) {
    return {p1.x * p2.x, p1.y * p2.y, p1.z * p2.z};
}

//a+=b
template<typename T>
Point3<T>& operator+=(Point3<T>& p1, const Point3<T>& p2) {
    p1.x += p2.x;
    p1.y += p2.y;
    p1.z += p2.z;
    return p1;
}

//p+=v
template<typename T>
Point3<T>& operator+=(Point3<T>& p, const Vector3<T>& v) {
    p.x += v.x;
    p.y += v.y;
    p.z += v.z;
    return p;
}

//a-=b
template<typename T>
Point3<T>& operator-=(Point3<T>& p1, const Point3<T>& p2) {
    p1.x -= p2.x;
    p1.y -= p2.y;
    p1.z -= p2.z;
    return p1;
}

//p-=v
template<typename T>
Point3<T>& operator-=(Point3<T>& p, const Vector3<T>& v) {
    p.x -= v.x;
    p.y -= v.y;
    p.z -= v.z;
    return p;
}

//a*=b
template<typename T>
Point3<T>& operator*=(Point3<T>& p1, const Point3<T>& p2) {
    p1.x *= p2.x;
    p1.y *= p2.y;
    p1.z *= p2.z;
    return p1;
}

//a*=k
template<typename T, typename U>
Point3<T>& operator*=(Point3<T>& p, U k) {
    p.x *= k;
    p.y *= k;
    p.z *= k;
    return p;
}

//a/=k
template<typename T, typename U>
Point3<T>& operator/=(Point3<T>& p, U k) {
    assert(k != 0);
    p.x /= k;
    p.y /= k;
    p.z /= k;
    return p;
}

//p=a*k
template<typename T, typename U>
Point3<T> operator*(const Point3<T>& p, U k) {
    return {p.x * k, p.y * k, p.z * k};
}

//p=k*a
template<typename T, typename U>
Point3<T> operator*(U k, const Point3<T>& p) {
    return {p.x * k, p.y * k, p.z * k};
}

//p=a/k
template<typename T, typename U>
Point3<T> operator/(const Point3<T>& p, U k) {
    assert(k != 0);
    return {p.x / k, p.y / k, p.z / k};
}

//p=a==b
template<typename T>
bool operator==(const Point3<T>& p1, const Point3<T>& p2) {
    return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
}

//p=a!=b
template<typename T>
bool operator!=(const Point3<T>& p1, const Point3<T>& p2) {
    return p1.x != p2.x || p1.y != p2.y || p1.z != p2.z;
}

//p=a<b
template<typename T>
bool operator<(const Point3<T>& p1, const Point3<T>& p2) {
    return p1.x < p2.x && p1.y < p2.y && p1.z < p2.z;
}

//p=a<=b
template<typename T>
bool operator<=(const Point3<T>& p1, const Point3<T>& p2) {
    return p1.x <= p2.x && p1.y <= p2.y && p1.z <= p2.z;
}

//p=a>b
template<typename T>
bool operator>(const Point3<T>& p1, const Point3<T>& p2) {
    return p1.x > p2.x && p1.y > p2.y && p1.z > p2.z;
}

//p=a>=b
template<typename T>
bool operator>=(const Point3<T>& p1, const Point3<T>& p2) {
    return p1.x >= p2.x && p1.y >= p2.y && p1.z >= p2.z;
}

//ostream
template<typename T>
std::ostream& operator<<(std::ostream& os, const Point3<T>& p) {
    os << "[ " << p.x << ", " << p.y << ", " << p.z << " ]";
    return os;
}

//Distance
template<typename T>
T Distance(const Point3<T>& p1, const Point3<T>& p2) {
    return (p1 - p2).Length();
}

//DistanceSquared
template<typename T>
T DistanceSquared(const Point3<T>& p1, const Point3<T>& p2) {
    return (p1 - p2).LengthSquared();
}

//Lerp
template<typename T>
Point3<T> Lerp(const Point3<T>& p1, const Point3<T>& p2, T t) {
    return (1 - t) * p1 + t * p2;
}

//Min
template<typename T>
Point3<T> Min(const Point3<T>& p1, const Point3<T>& p2) {
    return {std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)};
}

//Max
template<typename T>
Point3<T> Max(const Point3<T>& p1, const Point3<T>& p2) {
    return {std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z)};
}

//Floor
template<typename T>
Point3<T> Floor(const Point3<T>& p) {
    return {std::floor(p.x), std::floor(p.y), std::floor(p.z)};
}

//Ceil
template<typename T>
Point3<T> Ceil(const Point3<T>& p) {
    return {std::ceil(p.x), std::ceil(p.y), std::ceil(p.z)};
}

//Abs
template<typename T>
Point3<T> Abs(const Point3<T>& p) {
    return {std::abs(p.x), std::abs(p.y), std::abs(p.z)};
}

using Point3f = Point3<float>;
using Point3i = Point3<int>;
}