#pragma once

#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>

namespace Just {
    //全局变量
    constexpr float kPI = 3.14159265358979323846f;
    constexpr float kInvPI = 0.31830988618379067154f;
    constexpr float kInv2PI = 0.15915494309189533577f;
    constexpr float kInv4PI = 0.07957747154594766788f;
    constexpr float kSqrt2 = 1.41421356237309504880f;
    constexpr float kEpsilon = 1e-4f;

    constexpr float kFloatMax = std::numeric_limits<float>::max();
    constexpr float kFloatLower = std::numeric_limits<float>::lowest();

    //打印
    template<typename T, typename ... U>
    inline void Print(T first, U ... rest) {
        if constexpr (sizeof...(rest)) {
            std::cout << first << std::endl;
            Print(rest...);
        } else {
            std::cout << first << std::endl;
        }
    }

    //角度和弧度互转
    inline float Radians(float deg) {
        return kPI / 180.0f * deg;
    }

    inline float Degrees(float rad) {
        return 180.0f / kPI * rad;
    }

}