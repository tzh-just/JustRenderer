//================================================
// 二维矢量
//================================================

#pragma once

#include <Global.h>

namespace just
{

    template<typename T>
    struct Vector2
    {
        using Vector = Vector2<T>;

        union
        {
            struct
            {
                T x, y;
            };
            T data[2];
        };

        constexpr Vector2() : x(0), y(0) {}

        constexpr explicit Vector2(T val) : x(val), y(val) {}

        constexpr Vector2(T v1, T v2, T v3) : x(v1), y(v2) {}

        constexpr Vector2(const std::initializer_list<T>& list)
        {
            auto it = list.begin();
            for (size_t i = 0; i < 2; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T& operator[](size_t i)
        {
            assert(i < 2);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < 2);
            return data[i];
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector& v)
        {
            return os << "(" << v.x << "," << v.y << ")";
        }

        constexpr T Length() const { return std::sqrt(x * x + y * y); }

        constexpr T Dot(const Vector& v) const { return x * v.x + y * v.y; }

        constexpr T Cross(const Vector& v) { return {x * v.y - v.x * y}; }

        constexpr Vector Normalize() const { return (*this) / Length(); }

    };

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;

}



