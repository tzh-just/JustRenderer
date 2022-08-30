#pragma once

#include "Geometry/Transform.h"
#include "Geometry/Bounds3.h"

namespace Just {
    struct Shape {
        std::shared_ptr<Transform> objToWorld;
        std::shared_ptr<Transform> worldToObj;

        Shape(const std::shared_ptr<Transform>& objToWorld, const std::shared_ptr<Transform>& worldToObj) {
            this->objToWorld = objToWorld;
            this->worldToObj = worldToObj;
        }

        virtual Bounds3f ObjectBound() const = 0;

        virtual Bounds3f WorldBound() const = 0;
    };
}