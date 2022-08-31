#pragma once

#include "Global.h"

namespace Just {
    template<typename T>
    struct Color3 {
        T r, g, b;

        Color3() : r(T()), g(T()), b(T()) {}

        explicit Color3(T val) : r(val), g(val), b(val) {}

        Color3(T r, T g, T b) : r(r), g(g), b(b) {}

        T& operator[](size_t i) {
            assert(i < 3);
            return (&r)[i];
        }

        T operator[](size_t i) const {
            assert(i < 3);
            return (&r)[i];
        }

        T GrayScale() {
            return 0.299f * r + 0.587f * g + 0.114f * b;
        }
    };

    //加法
    template<typename T>
    inline Color3<T> operator+(const Color3<T>& c1, const Color3<T>& c2) {
        return Color3<T>(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
    }

    //赋值加
    template<typename T>
    inline Color3<T>& operator+=(Color3<T>& c1, const Color3<T>& c2) {
        c1.r += c2.r;
        c1.g += c2.g;
        c1.b += c2.b;
        return c1;
    }

    //减法
    template<typename T>
    inline Color3<T> operator-(const Color3<T>& c1, const Color3<T>& c2) {
        return Color3<T>(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
    }

    //赋值减
    template<typename T>
    inline Color3<T>& operator-=(Color3<T>& c1, const Color3<T>& c2) {
        c1.r -= c2.r;
        c1.g -= c2.g;
        c1.b -= c2.b;
        return c1;
    }

    //乘法
    template<typename T>
    inline Color3<T> operator*(const Color3<T>& c1, const Color3<T>& c2) {
        return Color3<T>(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
    }

    //赋值乘
    template<typename T>
    inline Color3<T> operator*=(const Color3<T>& c1, const Color3<T>& c2) {
        c1.r *= c2.r;
        c1.g *= c2.g;
        c1.b *= c2.b;
        return c1;
    }

    //后数乘
    template<typename T>
    inline Color3<T> operator*(const Color3<T>& c, T k) {
        return Color3<T>(c.r * k, c.g * k, c.b * k);
    }

    //前数乘
    template<typename T>
    inline Color3<T> operator*(T k, const Color3<T>& c) {
        return c * k;
    }

    //赋值数乘
    template<typename T>
    inline Color3<T>& operator*=(Color3<T>& c, T k) {
        assert(!std::isnan(k));
        c.r *= k;
        c.g *= k;
        c.b *= k;
        return c;
    }

    //数除
    template<typename T>
    inline Color3<T> operator/(const Color3<T>& c, T k) {
        assert(k != 0);
        float inv = (float) 1 / k;
        return Color3<T>(c.r * inv, c.g * inv, c.b * inv);
    }

    //赋值数除
    template<typename T, typename U>
    inline Color3<T>& operator/=(Color3<T>& c, U k) {
        assert(k != 0);
        float inv = (float) 1 / k;
        c.r *= inv;
        c.g *= inv;
        c.b *= inv;
        return c;
    }

    using RGB = Color3<int>;
    using Spectrum = Color3<float>;

    inline Spectrum RGB2Spectrum(const RGB& rgb) {
        return {
                std::clamp(float(rgb.r) / 255.0f, 0.0f, 1.0f),
                std::clamp(float(rgb.g) / 255.0f, 0.0f, 1.0f),
                std::clamp(float(rgb.b) / 255.0f, 0.0f, 1.0f)
        };
    }

    inline RGB Spectrum2RGB(const Spectrum& spectrum) {
        return {
                std::clamp(int(spectrum.r * 255), 0, 255),
                std::clamp(int(spectrum.g * 255), 0, 255),
                std::clamp(int(spectrum.b * 255), 0, 255)
        };
    }
}