#pragma once

#include "Math/Vector.h"

namespace Just {
    struct Ray3f {
        Point3f origin;
        Vector3f direction;
        mutable float tMax;

        Ray3f() : tMax(kFloatMax) {}

        Ray3f(const Point3f& origin, const Vector3f& direction) :
                origin(origin), direction(direction), tMax(kFloatMax) {}

        Point3f At(float t) const {
            return origin + direction * t;
        }
    };
}
