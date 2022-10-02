#pragma once

#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>

namespace Just {

// Global Forward Declarations
template<typename T>
struct Point2;
template<typename T>
struct Point3;
template<typename T>
struct Vector2;
template<typename T>
struct Vector3;
template<typename T>
struct Color3;
template<typename T>
struct Bounds2;
template<typename T>
struct Bounds3;

struct Ray;
struct Transform;


// Global Constants
float kPI = 3.14159265358979323846f;
float kInvPI = 0.31830988618379067154f;
float kInv2PI = 0.15915494309189533577f;
float kInv4PI = 0.07957747154594766788f;
float kSqrt2 = 1.41421356237309504880f;
float kEpsilon = 1e-4f;

float kFloatMax = std::numeric_limits<float>::max();
float kFloatLower = std::numeric_limits<float>::lowest();

// Global Functions
template<typename T, typename ... U>
inline void Print(T first, U ... rest) {
    if (sizeof...(rest)) {
        std::cout << first << std::endl;
        Print(rest...);
    } else {
        std::cout << first << std::endl;
    }
}

inline float Radians(float deg) {
    return kPI / 180.0f * deg;
}

inline float Degrees(float rad) {
    return 180.0f / kPI * rad;
}

//ref:pbrt-v3
template<typename T, typename U, typename V>
inline T Clamp(T value, U low, V high) {
    return value < low ? low : (value > high ? high : value);
}
}