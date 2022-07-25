//================================================
// 全局
//================================================

#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

namespace Just {
    //全局变量
    //-------------------------------------------------------------------------
    static constexpr float PI = 3.14159265358979323846f;
    static constexpr float InvPI = 0.31830988618379067154f;
    static constexpr float Inv2PI = 0.15915494309189533577f;
    static constexpr float Inv4PI = 0.07957747154594766788f;
    static constexpr float Sqrt2 = 1.41421356237309504880;

    static constexpr float EPSILON = 1e-4f;
    //全局函数
    //-------------------------------------------------------------------------

    //打印
    template<typename T, typename ... U>
    inline void Print(T first, U ... rest) {
        if constexpr(sizeof...(rest)) {
            std::cout << first << std::endl;
            Print(rest...);
        } else {
            std::cout << first << std::endl;
        }
    }

    //
    template<typename T, typename U, typename V>
    inline T Clamp(T val, U low, V high) {
        if (val < low) return low;
        else if (val > high) return high;
        else return val;
    }

    //角度和弧度互转
    inline float Radians(float deg) {
        return PI / 180.0f * deg;
    }

    inline float Degrees(float rad) {
        return 180.0f / PI * rad;
    }

}