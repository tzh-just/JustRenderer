//================================================
// 四维矢量
//================================================

#pragma once

#include "Global.h"

namespace Just
{

    template<typename T>
    struct Vector4
    {
        using Vector = Vector4<T>;

        union
        {
            struct
            {
                T x, y, z, w;
            };
            T data[4];
        };

        constexpr Vector4() : x(0), y(0), z(0), w(0) {}

        constexpr explicit Vector4(T val) : x(val), y(val), z(val), w(val) {}

        constexpr Vector4(T v1, T v2, T v3, T v4) : x(v1), y(v2), z(v3), w(v4) {}

        constexpr Vector4(const std::initializer_list<T>& list)
        {
            auto it = list.begin();
            for (size_t i = 0; i < 4; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T& operator[](size_t i)
        {
            assert(i < 4);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < 4);
            return data[i];
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector& v)
        {
            return os << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
        }

        constexpr T Dot(const Vector& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
    };

    using Vector4f = Vector4<float>;

}



