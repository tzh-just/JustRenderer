#pragma once

#include <vector>

#include "Geometry/Bounds.h"
#include "Accel.h"

namespace Just {
    struct BVHNode{
        unsigned int child = 0;
        Bounds3f bbox;
        std::vector<int> indices;

        BVHNode() : bbox() {}

        explicit BVHNode(Bounds3f bbox) : bbox(std::move(bbox)) {}
    };

    class BVH : Accel {

    };
}