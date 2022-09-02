#pragma once

#include "Math/Transform.h"
#include "Geometry/Bounds.h"

namespace Just {
    struct Shape {
        std::shared_ptr<Transform> objToWorld;
        std::shared_ptr<Transform> worldToObj;

        Shape(std::shared_ptr<Transform> objToWorld, std::shared_ptr<Transform> worldToObj)
                : objToWorld(objToWorld), worldToObj(worldToObj) {}

        virtual Bounds3f ObjectBound() const = 0;

        virtual Bounds3f WorldBound() const = 0;
    };
}