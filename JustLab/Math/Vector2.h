//================================================
// 二维矢量
//================================================

#pragma once

#include "Global.h"

namespace Just
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
    };

    //各维度最小值
    template<typename T>
    constexpr Vector2<T> MinVector(const Vector2<T>& v1, const Vector2<T>& v2)
    {
        Vector2<T> min;
        for (size_t i = 0; i < 2; ++i)
        {
            min[i] = std::min(v1[i], v2[i]);
        }
        return min;
    }

    //各维度最大值
    template<typename T>
    constexpr Vector2<T> MaxVector(const Vector2<T>& v1, const Vector2<T>& v2)
    {
        Vector2<T> max;
        for (size_t i = 0; i < 2; ++i)
        {
            max[i] = std::max(v1[i], v2[i]);
        }
        return max;
    }

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;

}



