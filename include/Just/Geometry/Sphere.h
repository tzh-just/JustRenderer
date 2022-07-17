#pragma once

#include "Just/Math/Vector.h"
#include "Just/Graphic/Transform.h"
#include "Ray.h"

namespace Just {

    struct Sphere : Hittable{
        Transform transform;
        float radius;

        Sphere(const Transform &trans, float r) : transform(trans), radius(r) {}
    };
}
