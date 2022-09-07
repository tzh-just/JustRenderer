#pragma once

#include "Global.h"

namespace Just {

template<typename T>
struct Color3 {
    T r, g, b;

    Color3() : r(0), g(0), b(0) {}

    explicit Color3(T value = 0) : r(value), g(value), b(value) {}

    Color3(T r, T g, T b) : r(r), g(g), b(b) {}

    T operator[](size_t i) const {
        assert(i < 3);
        return (&r)[i];
    }

    T& operator[](size_t i) {
        assert(i < 3);
        return (&r)[i];
    }

    bool HasNaNs() const {
        return std::isnan(r) || std::isnan(g) || std::isnan(b);
    }
};

//c=-a
template<typename T>
Color3<T> operator-(const Color3<T>& c) {
    return {-c.x, -c.y, -c.z};
}

//c=a+b
template<typename T>
Color3<T> operator+(const Color3<T>& c1, const Color3<T>& c2) {
    return {c1.x + c2.x, c1.y + c2.y, c1.z + c2.z};
}

//c=a-b
template<typename T>
Color3<T> operator-(const Color3<T>& c1, const Color3<T>& c2) {
    return {c1.x - c2.x, c1.y - c2.y};
}

//c=a*b
template<typename T>
Color3<T> operator*(const Color3<T>& c1, const Color3<T>& c2) {
    return {c1.x * c2.x, c1.y * c2.y, c1.z * c2.z};
}

//a+=b
template<typename T>
Color3<T>& operator+=(Color3<T>& c1, const Color3<T>& c2) {
    c1.x += c2.x;
    c1.y += c2.y;
    c1.z += c2.z;
    return c1;
}

//a-=b
template<typename T>
Color3<T>& operator-=(Color3<T>& c1, const Color3<T>& c2) {
    c1.x -= c2.x;
    c1.y -= c2.y;
    c1.z -= c2.z;
    return c1;
}

//a*=b
template<typename T>
Color3<T>& operator*=(Color3<T>& c1, const Color3<T>& c2) {
    c1.x *= c2.x;
    c1.y *= c2.y;
    c1.z *= c2.z;
    return c1;
}

//a*=k
template<typename T, typename U>
Color3<T>& operator*=(Color3<T>& c, U k) {
    c.x *= k;
    c.y *= k;
    c.z *= k;
    return c;
}

//a/=k
template<typename T, typename U>
Color3<T>& operator/=(Color3<T>& c, U k) {
    assert(k != 0);
    c.x /= k;
    c.y /= k;
    c.z /= k;
    return c;
}

//c=a*k
template<typename T, typename U>
Color3<T> operator*(const Color3<T>& c, U k) {
    return {c.x * k, c.y * k, c.z * k};
}

//c=k*a
template<typename T, typename U>
Color3<T> operator*(U k, const Color3<T>& c) {
    return {c.x * k, c.y * k, c.z * k};
}

//c=a/k
template<typename T, typename U>
Color3<T> operator/(const Color3<T>& c, U k) {
    assert(k != 0);
    return {c.x / k, c.y / k, c.z / k};
}

//a==b
template<typename T>
bool operator==(const Color3<T>& c1, const Color3<T>& c2) {
    return c1.x == c2.x && c1.y == c2.y && c1.z == c2.z;
}

//a!=b
template<typename T>
bool operator!=(const Color3<T>& c1, const Color3<T>& c2) {
    return c1.x != c2.x || c1.y != c2.y || c1.z != c2.z;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Color3<T>& c) {
    os << "[ " << c.x << ", " << c.y << ", " << c.z << " ]";
    return os;
}

//Lerp
template<typename T>
inline Color3<T> Lerp(float t, const Color3<T>& c1, const Color3<T>& c2) {
    return (1 - t) * c1 + t * c2;
}

//Sqrt
template<typename T>
inline Color3<T> Sqrt(const Color3<T>& s) {
    return {std::sqrt(s.x), std::sqrt(s.y), std::sqrt(s.z)};
}

//Clamp
template<typename T>
inline Color3<T> Clamp(const Color3<T>& s, float low, float high) {
    return {std::clamp(s.x, low, high), std::clamp(s.y, low, high), std::clamp(s.z, low, high)};
}

using Spectrum = Color3<float>;
using RGB = Color3<uint8_t>;

inline Spectrum ToSpectrum(const RGB& color) {
    return {
            float(color.r) / 255.0f,
            float(color.g) / 255.0f,
            float(color.b) / 255.0f
    };
}

inline RGB ToRGB(const Spectrum& color) {
    return {
            uint8_t(std::clamp(255.f * color.r, 0.0f, 255.0f)),
            uint8_t(std::clamp(255.f * color.g, 0.0f, 255.0f)),
            uint8_t(std::clamp(255.f * color.b, 0.0f, 255.0f))
    };
}
}