#pragma once

#include "Just/Math/Vector.h"
#include "Just/Graphic/Transform.h"

namespace Just {

    struct Sphere {
        Transform transform;
        float radius;

        Sphere(const Transform &trans, float r) : transform(trans), radius(r) {}
    };
}
