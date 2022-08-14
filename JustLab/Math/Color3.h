//================================================
// RGB颜色
//================================================

#pragma once

#include "Global.h"

namespace Just
{

    template<typename T>
    struct Color3
    {
        using Color = Color3<T>;

        union
        {
            struct
            {
                T r, g, b;
            };
            T data[3];
        };

        constexpr Color3() : r(0), g(0), b(0) {}

        constexpr explicit Color3(T val) : r(val), g(val), b(val) {}

        constexpr Color3(T v1, T v2, T v3) : r(v1), g(v2), b(v3) {}

        constexpr Color3(const std::initializer_list<T>& list)
        {
            auto it = list.begin();
            for (size_t i = 0; i < 3; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T& operator[](size_t i)
        {
            assert(i < 3);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < 3);
            return data[i];
        }

        friend std::ostream& operator<<(std::ostream& os, const Color& v)
        {
            return os << "(" << v.r << "," << v.g << "," << v.b << ")";
        }

        //四则运算
        constexpr Color operator+(const Color& v) const { return {r + v.r, g + v.g, b + v.b}; }

        constexpr Color operator-(const Color& v) const { return {r - v.r, g - v.g, b - v.b}; }

        constexpr Color operator*(const Color& v) const { return {r * v.r, g * v.g, b * v.b}; }

        constexpr Color operator/(const Color& v) const { return {r / v.r, g / v.g, b / v.b}; }

        constexpr void operator+=(const Color& v)
        {
            r += v.r;
            g += v.g;
            b += v.b;
        }

        constexpr void operator-=(const Color& v)
        {
            r -= v.r;
            g -= v.g;
            b -= v.b;
        }

        constexpr void operator*=(const Color& v)
        {
            r *= v.r;
            g *= v.g;
            b *= v.b;
        }

        constexpr void operator/=(const Color& v)
        {
            r /= v.r;
            g /= v.g;
            b /= v.b;
        }

        //数乘
        constexpr Color operator*(T k) const { return {r * k, g * k, b * k}; }

        constexpr friend Color operator*(T k, const Color& v) { return {v.r * k, v.g * k, v.b * k}; }

        constexpr Color operator/(T k) const { return {r / k, g / k, b / k}; }

        constexpr void operator*=(T k)
        {
            r *= k;
            g *= k;
            b *= k;
        }

        constexpr void operator/=(T k)
        {
            r /= k;
            g /= k;
            b /= k;
        }

        constexpr T GrayScale() const { return 0.299f * r + 0.587f * g + 0.114f * b; }
    };

    using Color3f = Color3<float>;

}



