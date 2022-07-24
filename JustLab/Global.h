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
    constexpr float M_PI = 3.14159265358979323846f;
    constexpr float INV_PI = 0.31830988618379067154f;
    constexpr float INV_PI2 = 0.15915494309189533577f;
    constexpr float INV_PI4 = 0.07957747154594766788f;
    constexpr float EPS = 1e-4f;

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

    //角度和弧度互转
    inline float Radians(float deg) {
        return M_PI / 180.0f * deg;
    }

    inline float Degrees(float rad) {
        return 180.0f / M_PI * rad;
    }

    //三角函数
    inline float Sin(float degree) {
        auto radian = Radians(degree);
        return std::sin(radian);
    }

    inline float Cos(float degree) {
        auto radian = Radians(degree);
        return std::cos(radian);
    }

    inline float Tan(float degree) {
        auto radian = Radians(degree);
        return std::tan(radian);
    }
}