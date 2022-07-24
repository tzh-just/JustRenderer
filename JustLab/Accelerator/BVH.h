#pragma once

#include "Geometry/Bounds.h"
#include "Accelerator.h"

namespace Just {
    struct BVHNode{
        unsigned int child = 0;
        Bounds3f bbox;
        std::vector<unsigned int> indices;

        BVHNode() : bbox() {}

        explicit BVHNode(Bounds3f bbox) : bbox(std::move(bbox)) {}
    };

    class BVH : Accelerator {

    };
}