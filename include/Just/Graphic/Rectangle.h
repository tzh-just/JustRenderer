#pragma once

#include "Just/Math/Vector.h"
#include "Just/Graphic/Transform.h"

namespace Just {

    struct Rectangle {
        Transform transform;
        float radius;

        Rectangle(const Transform &trans, float r) : transform(trans), radius(r) {}
    };
}