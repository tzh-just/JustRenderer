#pragma once

#include "Math/Vector.h"

namespace Just {
    struct Ray3f {
        Point3f origin;
        Vector3f direction;
        mutable float hitTime;

        Ray3f() : hitTime(kFloatMax) {}

        Ray3f(const Point3f& origin, const Vector3f& direction) :
                origin(origin), direction(direction), hitTime(kFloatMax) {}

        Point3f At(float t) const {
            return origin + direction * t;
        }
    };
}
