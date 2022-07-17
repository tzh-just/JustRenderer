//================================================
// 全局
//
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

    //工具函数
    //-------------------------------------------------------------------------
    //三角函数
    template<typename T>
    inline T Sin(T degree) {
        auto radian = ConvertDegreesToRadians(degree);
        return std::sin(radian);
    }

    template<typename T>
    inline T Cos(T degree) {
        auto radian = ConvertDegreesToRadians(degree);
        return std::cos(radian);
    }

    template<typename T>
    inline T Tan(T degree) {
        auto radian = ConvertDegreesToRadians(degree);
        return std::tan(radian);
    }

    //角度和弧度互转
    template<typename T>
    inline T ConvertDegreesToRadians(T degree) {
        return degree * PI / 180.0f;
    }

    template<typename T>
    inline T ConvertRadiansToDegrees(T radian) {
        return radian * 180.0f / PI;
    }
}