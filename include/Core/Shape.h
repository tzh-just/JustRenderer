#pragma once

#include "Math/Transform.h"
#include "Geometry/Bounds.h"

namespace Just {
struct Shape {
    const Transform* transform;

    Shape() = default;

    explicit Shape(Transform* transform) : transform(transform) {}
};
}