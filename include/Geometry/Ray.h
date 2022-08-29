#pragma once

#include "Math/Vector3.h"
#include "Math/Point3.h"

namespace Just {
    struct Ray {
        Point3f origin;
        Vector3f direction;
        mutable float tMax;

        Ray() : tMax(kFloatMax) {}

        Ray(const Point3f& origin, const Vector3f& direction) :
                origin(origin), direction(direction), tMax(kFloatMax) {}

        Point3f At(float t) const{
            return origin + direction * t;
        }
    };
}
