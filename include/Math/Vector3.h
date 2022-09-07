#pragma once

#include "Global.h"

namespace Just {
template<typename T>
struct Vector3 {
    T x, y, z;

    //构造函数
    Vector3() : x(T()), y(T()), z(T()) {}

    explicit Vector3(T val) : x(val), y(val), z(val) {}

    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

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

    T Length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    T LengthSquared() const {
        return x * x + y * y + z * z;
    }
};


//v=-a
template<typename T>
Vector3<T> operator-(const Vector3<T>& v) {
    return {-v.x, -v.y, -v.z};
}

//v=a+b
template<typename T>
Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

//v=a-b
template<typename T>
Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

//v=a*b
template<typename T>
Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2) {
    return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

//a+=b
template<typename T>
Vector3<T>& operator+=(Vector3<T>& v1, const Vector3<T>& v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

//a-=b
template<typename T>
Vector3<T>& operator-=(Vector3<T>& v1, const Vector3<T>& v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

//a*=b
template<typename T>
Vector3<T>& operator*=(Vector3<T>& v1, const Vector3<T>& v2) {
    v1.x *= v2.x;
    v1.y *= v2.y;
    v1.z *= v2.z;
    return v1;
}

//a*=k
template<typename T, typename U>
Vector3<T>& operator*=(Vector3<T>& v, U k) {
    v.x *= k;
    v.y *= k;
    v.z *= k;
    return v;
}

//a/=k
template<typename T, typename U>
Vector3<T>& operator/=(Vector3<T>& v, U k) {
    assert(k != 0);
    v.x /= k;
    v.y /= k;
    v.z /= k;
    return v;
}

//v=a*k
template<typename T, typename U>
Vector3<T> operator*(const Vector3<T>& v, U k) {
    return {v.x * k, v.y * k, v.z * k};
}

//v=k*a
template<typename T, typename U>
Vector3<T> operator*(U k, const Vector3<T>& v) {
    return {v.x * k, v.y * k, v.z * k};
}

//v=a/k
template<typename T, typename U>
Vector3<T> operator/(const Vector3<T>& v, U k) {
    assert(k != 0);
    return {v.x / k, v.y / k, v.z / k};
}

//v=a==b
template<typename T>
bool operator==(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

//v=a!=b
template<typename T>
bool operator!=(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}

//v=a<b
template<typename T>
bool operator<(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z;
}

//v=a<=b
template<typename T>
bool operator<=(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z;
}

//v=a>b
template<typename T>
bool operator>(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z;
}

//v=a>=b
template<typename T>
bool operator>=(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) {
    os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    return os;
}

//v=|a|
template<typename T>
Vector3<T> Abs(const Vector3<T>& v) {
    return {std::abs(v.x), std::abs(v.y), std::abs(v.z)};
}

//向量点乘
template<typename T>
T Dot(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//向量点乘
template<typename T>
T AbsDot(const Vector3<T>& v1, const Vector3<T>& v2) {
    return std::abs(Dot(v1, v2));
}

//向量叉乘
template<typename T>
Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2) {
    return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}

//向量归一化
template<typename T>
Vector3<T> Normalize(const Vector3<T>& v) {
    return v / v.Length();
}

//最小维度的值
template<typename T>
T MinComponent(const Vector3<T>& v) {
    return std::min(v.x, std::min(v.y, v.z));
}

//最大维度的值
template<typename T>
T MaxComponent(const Vector3<T>& v) {
    return std::max(v.x, std::max(v.y, v.z));
}

//两向量取各维度最小值组成新的向量
template<typename T>
Vector3<T> Min(const Vector3<T>& v1, const Vector3<T>& v2) {
    return {std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z)};
}

//两向量取各维度最大值组成新的向量
template<typename T>
Vector3<T> Max(const Vector3<T>& v1, const Vector3<T>& v2) {
    return {std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z)};
}

//两向量取各维度最大值组成新的向量
template<typename T>
T MaxDimension(const Vector3<T>& v) {
    return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}

using Vector3f = Vector3<float>;
}