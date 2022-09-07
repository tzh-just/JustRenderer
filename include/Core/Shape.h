#pragma once

#include "Math/Transform.h"
#include "Geometry/Bounds.h"

namespace Just {
struct Shape {
    std::shared_ptr<Transform> transform;

    Shape() = default;

    explicit Shape(std::shared_ptr<Transform> transform) : transform(transform) {}
};
}