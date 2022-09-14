#pragma once

#include "Math/Vector3.h"
#include "Math/Point3.h"

namespace Just {
struct Ray {
    Point3f origin;
    //射线方向是一个单位向量，有利于计算
    Vector3f direction;
    mutable float tMax;
    //Ref: RT Gems
    mutable float tMin;

    Ray() : tMax(kFloatMax), tMin(kEpsilon) {}

    Ray(const Point3f& origin, const Vector3f& direction) :
            origin(origin), direction(Normalize(direction)), tMax(kFloatMax), tMin(kEpsilon) {}

    //Ref: rt in one weekend
    Point3f At(float t) const {
        return origin + direction * t;
    }
};

struct RayDifferential {

};
}
