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
    constexpr float PI = 3.1415926f;
    constexpr float EPS = 0.001f;

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
    inline float ConvertDegreesToRadians(float degree) {
        return degree * PI / 180.0f;
    }

    inline float ConvertRadiansToDegrees(float radian) {
        return radian * 180.0f / PI;
    }

    //三角函数
    inline float Sin(float degree) {
        auto radian = ConvertDegreesToRadians(degree);
        return std::sin(radian);
    }

    inline float Cos(float degree) {
        auto radian = ConvertDegreesToRadians(degree);
        return std::cos(radian);
    }

    inline float Tan(float degree) {
        auto radian = ConvertDegreesToRadians(degree);
        return std::tan(radian);
    }
}