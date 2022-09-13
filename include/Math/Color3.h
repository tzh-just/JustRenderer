#pragma once

#include "Global.h"

namespace Just {

template<typename T>
struct Color3 {
    T r, g, b;

    Color3() : r(T()), g(T()), b(T()) {}

    explicit Color3(T value) : r(value), g(value), b(value) {}

    Color3(T r, T g, T b) : r(r), g(g), b(b) {}

    T operator[](size_t i) const {
        assert(i < 3);
        return (&r)[i];
    }

    T& operator[](size_t i) {
        assert(i < 3);
        return (&r)[i];
    }

    //clear
    void Clear() {
        r = g = b = T();
    }
};

//c=-a
template<typename T>
Color3<T> operator-(const Color3<T>& c) {
    return {-c.r, -c.g, -c.b};
}

//c=a+b
template<typename T>
Color3<T> operator+(const Color3<T>& c1, const Color3<T>& c2) {
    return {c1.r + c2.r, c1.g + c2.g, c1.b + c2.b};
}

//c=a-b
template<typename T>
Color3<T> operator-(const Color3<T>& c1, const Color3<T>& c2) {
    return {c1.r - c2.r, c1.g - c2.g};
}

//c=a*b
template<typename T>
Color3<T> operator*(const Color3<T>& c1, const Color3<T>& c2) {
    return {c1.r * c2.r, c1.g * c2.g, c1.b * c2.b};
}

//a+=b
template<typename T>
Color3<T>& operator+=(Color3<T>& c1, const Color3<T>& c2) {
    c1.r += c2.r;
    c1.g += c2.g;
    c1.b += c2.b;
    return c1;
}

//a-=b
template<typename T>
Color3<T>& operator-=(Color3<T>& c1, const Color3<T>& c2) {
    c1.r -= c2.r;
    c1.g -= c2.g;
    c1.b -= c2.b;
    return c1;
}

//a*=b
template<typename T>
Color3<T>& operator*=(Color3<T>& c1, const Color3<T>& c2) {
    c1.r *= c2.r;
    c1.g *= c2.g;
    c1.b *= c2.b;
    return c1;
}

//a*=k
template<typename T, typename U>
Color3<T>& operator*=(Color3<T>& c, U k) {
    c.r *= k;
    c.g *= k;
    c.b *= k;
    return c;
}

//a/=k
template<typename T, typename U>
Color3<T>& operator/=(Color3<T>& c, U k) {
    assert(k != 0);
    c.r /= k;
    c.g /= k;
    c.b /= k;
    return c;
}

//c=a*k
template<typename T, typename U>
Color3<T> operator*(const Color3<T>& c, U k) {
    return {c.r * k, c.g * k, c.b * k};
}

//c=k*a
template<typename T, typename U>
Color3<T> operator*(U k, const Color3<T>& c) {
    return {c.r * k, c.g * k, c.b * k};
}

//c=a/k
template<typename T, typename U>
Color3<T> operator/(const Color3<T>& c, U k) {
    assert(k != 0);
    return {c.r / k, c.g / k, c.b / k};
}

//a==b
template<typename T>
bool operator==(const Color3<T>& c1, const Color3<T>& c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

//a!=b
template<typename T>
bool operator!=(const Color3<T>& c1, const Color3<T>& c2) {
    return c1.r != c2.r || c1.g != c2.g || c1.b != c2.b;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Color3<T>& c) {
    os << "[ " << c.r << ", " << c.g << ", " << c.b << " ]";
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
    return {std::sqrt(s.r), std::sqrt(s.g), std::sqrt(s.b)};
}

//Clamp
template<typename T>
inline Color3<T> Clamp(const Color3<T>& s, float low, float high) {
    return {std::clamp(s.r, low, high), std::clamp(s.g, low, high), std::clamp(s.b, low, high)};
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

inline RGB ToSRGB(const Spectrum& color) {
    Spectrum result;
    for (int i = 0; i < 3; ++i) {
        float value = color[i];

        if (value <= 0.0031308f)
            result[i] = 12.92f * value;
        else
            result[i] = (1.0f + 0.055f)
                        * std::pow(value, 1.0f / 2.4f) - 0.055f;
    }
    return ToRGB(result);
}
}