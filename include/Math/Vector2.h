#pragma once

#include "Global.h"

namespace Just {
template<typename T>
struct Vector2 {
    T x, y;

    //构造函数
    Vector2() : x(T()), y(T()) {}

    explicit Vector2(T val) : x(val), y(val) {}

    Vector2(T x, T y) : x(x), y(y) {}

    //拷贝构造函数
    Vector2(const Vector2& v) {
        assert(!HasNaNs());
        x = v.x;
        y = v.y;
    }

    //拷贝赋值操作符重载
    Vector2<T>& operator=(const Vector2& v) {
        assert(!HasNaNs());
        x = v.x;
        y = v.y;
        return *this;
    }

    //合法性判断
    bool HasNaNs() const {
        return std::isnan(x) || isnan(y);
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

    T Length() const {
        return std::sqrt(x * x + y * y);
    }

    T LengthSquared() const {
        return x * x + y * y;
    }
};

//v=-a
template<typename T>
Vector2<T> operator-(const Vector2<T>& v) {
    return {-v.x, -v.y};
}

//v=a+b
template<typename T>
Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}

//v=a-b
template<typename T>
Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

//v=a*b
template<typename T>
Vector2<T> operator*(const Vector2<T>& v1, const Vector2<T>& v2) {
    return {v1.x * v2.x, v1.y * v2.y};
}

//a+=b
template<typename T>
Vector2<T>& operator+=(Vector2<T>& v1, const Vector2<T>& v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

//a-=b
template<typename T>
Vector2<T>& operator-=(Vector2<T>& v1, const Vector2<T>& v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

//a*=b
template<typename T>
Vector2<T>& operator*=(Vector2<T>& v1, const Vector2<T>& v2) {
    v1.x *= v2.x;
    v1.y *= v2.y;
    return v1;
}

//a*=k
template<typename T, typename U>
Vector2<T>& operator*=(Vector2<T>& v, U k) {
    v.x *= k;
    v.y *= k;
    return v;
}

//a/=k
template<typename T, typename U>
Vector2<T>& operator/=(Vector2<T>& v, U k) {
    v.x /= k;
    v.y /= k;
    return v;
}

//v=a*k
template<typename T, typename U>
Vector2<T> operator*(const Vector2<T>& v, U k) {
    return {v.x * k, v.y * k};
}

//v=k*a
template<typename T, typename U>
Vector2<T> operator*(U k, const Vector2<T>& v) {
    return {v.x * k, v.y * k};
}

//v=a/k
template<typename T, typename U>
Vector2<T> operator/(const Vector2<T>& v, U k) {
    return {v.x / k, v.y / k};
}

//v=a==b
template<typename T>
bool operator==(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x == v2.x && v1.y == v2.y;
}

//v=a!=b
template<typename T>
bool operator!=(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x != v2.x || v1.y != v2.y;
}

//v=a<b
template<typename T>
bool operator<(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x < v2.x && v1.y < v2.y;
}

//v=a<=b
template<typename T>
bool operator<=(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x <= v2.x && v1.y <= v2.y;
}

//v=a>b
template<typename T>
bool operator>(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x > v2.x && v1.y > v2.y;
}

//v=a>=b
template<typename T>
bool operator>=(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x >= v2.x && v1.y >= v2.y;
}

//ostream输出
template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
    os << "[ " << v.x << ", " << v.y << " ]";
    return os;
}

//v=|a|
template<typename T>
Vector2<T> Abs(const Vector2<T>& v) {
    return {std::abs(v.x), std::abs(v.y)};
}

//向量点乘
template<typename T>
T Dot(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

//向量点乘
template<typename T>
T AbsDot(const Vector2<T>& v1, const Vector2<T>& v2) {
    return std::abs(Dot(v1, v2));
}

//向量叉乘
template<typename T>
T Cross(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

//向量归一化
template<typename T>
Vector2<T> Normalize(const Vector2<T>& v) {
    return v / v.Length();
}

using Vector2f = Vector2<float>;
}