#pragma once

#include "Global.h"

namespace Just {
template<typename T>
struct Normal3 {
    T x, y, z;

    //构造函数
    Normal3() : x(T()), y(T()), z(T()) {}

    explicit Normal3(T val) : x(val), y(val), z(val) {
        assert(!HasNaNs());
    }

    explicit Normal3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z) {
        assert(!HasNaNs());
    }

    Normal3(T x, T y, T z) : x(x), y(y), z(z) {
        assert(!HasNaNs());
    }

    //拷贝构造函数
    Normal3(const Normal3& n) {
        assert(!HasNaNs());
        x = n.x;
        y = n.y;
        z = n.z;
    }

    //拷贝赋值操作符重载
    Normal3<T>& operator=(const Normal3& n) {
        assert(!HasNaNs());
        x = n.x;
        y = n.y;
        z = n.z;
        return *this;
    }

    //合法性判断
    bool HasNaNs() const {
        return std::isnan(x) || isnan(y) || isnan(z);
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

//n=-a
template<typename T>
Normal3<T> operator-(const Normal3<T>& n) {
    return {-n.x, -n.y, -n.z};
}

//n=a+b
template<typename T>
Normal3<T> operator+(const Normal3<T>& n1, const Normal3<T>& n2) {
    return {n1.x + n2.x, n1.y + n2.y, n1.z + n2.z};
}

//n1+=n2
template<typename T>
Normal3<T>& operator+=(Normal3<T>& n1, const Normal3<T>& n2) {
    n1.x += n2.x;
    n1.y += n2.y;
    n1.z += n2.z;
    return n1;
}

//n=a-b
template<typename T>
Normal3<T> operator-(const Normal3<T>& n1, const Normal3<T>& n2) {
    return {n1.x - n2.x, n1.y - n2.y, n1.z - n2.z};
}

//n1-=n2
template<typename T>
Normal3<T>& operator-=(Normal3<T>& n1, const Normal3<T>& n2) {
    n1.x -= n2.x;
    n1.y -= n2.y;
    n1.z -= n2.z;
    return n1;
}

//n=a*k
template<typename T, typename U>
Normal3<T> operator*(const Normal3<T>& n, U k) {
    return {n.x * k, n.y * k, n.z * k};
}

//n=k*a
template<typename T, typename U>
Normal3<T> operator*(U k, const Normal3<T>& n) {
    return {n.x * k, n.y * k, n.z * k};
}

//n/k
template<typename T, typename U>
Normal3<T> operator/(const Normal3<T>& n, U k) {
    assert(k != 0);
    return {n.x / k, n.y / k, n.z / k};
}

//n/=k
template<typename T, typename U>
Normal3<T>& operator/=(Normal3<T>& n, U k) {
    assert(k != 0);
    n.x /= k;
    n.y /= k;
    n.z /= k;
    return n;
}

//n1==n2
template<typename T>
bool operator==(const Normal3<T>& n1, const Normal3<T>& n2) {
    return n1.x == n2.x && n1.y == n2.y && n1.z == n2.z;
}

//n1!=n2
template<typename T>
bool operator!=(const Normal3<T>& n1, const Normal3<T>& n2) {
    return !(n1 == n2);
}

//ostream
template<typename T>
std::ostream& operator<<(std::ostream& os, const Normal3<T>& n) {
    os << "[ " << n.x << ", " << n.y << ", " << n.z << " ]";
    return os;
}

//Dot
template<typename T>
T Dot(const Normal3<T>& n1, const Normal3<T>& n2) {
    return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

//Abs
template<typename T>
Normal3<T> Abs(const Normal3<T>& n) {
    return {std::abs(n.x), std::abs(n.y), std::abs(n.z)};
}

//FaceForward
template<typename T>
Normal3<T> FaceForward(const Normal3<T>& n, const Vector3<T>& v) {
    return Dot(n, v) < 0 ? -n : n;
}

using Normal3f = Normal3<float>;
}