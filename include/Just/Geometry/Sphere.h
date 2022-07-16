#pragma once

#include "Just/Math/Vector.h"
#include "Transform.h"
#include "Ray.h"

namespace Just {

    struct Sphere : Hitable{
        Transform transform;
        float radius;

        Sphere(const Transform &trans, float r) : transform(trans), radius(r) {}
    };
}
