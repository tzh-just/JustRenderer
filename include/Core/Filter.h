#pragma once

#include "Math/Vector2.h"
#include "Math/Point2.h"

namespace Just {
struct Filter {
    //滤波器半径
    Vector2f radius;

    explicit Filter(const Vector2f& radius) : radius(radius) {}

    //计算滤波器权重
    virtual float Evaluate(const Point2f& p) const = 0;
};

struct BoxFilter : Filter {
    explicit BoxFilter(const Vector2f& radius = Vector2f(0.5f, 0.5f)) : Filter(radius) {}

    float Evaluate(const Point2f& p) const override {
        return 1.0f;
    }
};

struct TentFilter : Filter {
    explicit TentFilter(const Vector2f& radius = Vector2f(2.0f, 2.0f)) : Filter(radius) {}

    float Evaluate(const Point2f& p) const override {
        return std::max(0.0f, radius.x - std::abs(p.x)) *
               std::max(0.0f, radius.y - std::abs(p.y));
    }
};

struct GaussianFilter : Filter {

};

struct SobelFilter : Filter {

};


}