#pragma once

#include "Math/Vector3.h"
#include "Math/Point3.h"

namespace Just {
struct Ray {
    Point3f origin;
    //射线方向是一个单位向量，有利于计算
    Vector3f direction;
    mutable float tMax;
    //如果是相机发出的光线，tMin将被设置为为近平面距离，否则为一个很小的值
    mutable float tMin;

    Ray() : tMax(kFloatMax), tMin(kEpsilon) {}

    Ray(const Point3f& origin, const Vector3f& direction) :
            origin(origin), direction(Normalize(direction)), tMax(kFloatMax), tMin(kEpsilon) {}

    //不喜欢 pbrt 里的操作符重载，这里沿用 rt in one weekend 中的At函数
    Point3f At(float t) const {
        return origin + direction * t;
    }
};

struct RayDifferential {

};
}
