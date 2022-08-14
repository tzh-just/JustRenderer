//================================================
// 四维矢量
//================================================

#pragma once

#include "Global.h"

namespace Just
{

    template<typename T>
    struct Color4
    {
        using Color = Color4<T>;

        union
        {
            struct
            {
                T r, g, b, a;
            };
            T data[4];
        };

        constexpr Color4() : r(0), g(0), b(0), a(0) {}

        constexpr explicit Color4(T val) : r(val), g(val), b(val), a(val) {}

        constexpr Color4(T v1, T v2, T v3, T v4) : r(v1), g(v2), b(v3), a(v4) {}

        constexpr Color4(const std::initializer_list<T>& list)
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
    };

    using Color4f = Color4<float>;

}

