#pragma once

#include "Math/Vector2.h"
#include "Math/Point2.h"

namespace Just{
struct Filter{
    //滤波器半径
    Vector2f radius;

    explicit Filter(const Vector2f& radius) : radius(radius){}

    //计算滤波器权重
    virtual float Evaluate(const Point2f& p) const = 0;
};

struct BoxFilter{

};

struct TentFilter{

};

struct GaussianFilter{

};

struct SobelFilter{

};


}