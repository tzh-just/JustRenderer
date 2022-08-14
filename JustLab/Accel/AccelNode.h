#pragma once

#include <vector>
#include "Global.h"
#include "Hittable/Bounds3.h"

namespace Just{
    struct AccelNode
    {
        size_t child;
        BoundingBox3f bbox;
        std::vector<std::pair<size_t,size_t>> indexes;

        AccelNode() : bbox(), child(0) {}

        explicit AccelNode(const BoundingBox3f& bbox) : bbox(bbox), child(0) {}

        AccelNode(const BoundingBox3f& bbox, size_t size)
                : bbox(bbox), indexes(size), child(0) {}
    };
}