//================================================
// 全局
//================================================

#pragma once

#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <numeric>

namespace just{

//全局变量
//-------------------------------------------------------------------------
constexpr float kPI = 3.14159265358979323846f;
constexpr float kInvPI = 0.31830988618379067154f;
constexpr float kInv2PI = 0.15915494309189533577f;
constexpr float kInv4PI = 0.07957747154594766788f;
constexpr float kSqrt2 = 1.41421356237309504880;
constexpr float kEpsilon = 1e-4f;

//全局函数
//-------------------------------------------------------------------------
//最大小数
template<typename T>
constexpr T MaxValue(){
  return std::numeric_limits<double>::max();
}

template<typename T>
constexpr T MinValue(){
  return std::numeric_limits<float>::lowest();
}

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
  return kPI / 180.0f * deg;
}

inline float Degrees(float rad) {
  return 180.0f / kPI * rad;
}

}