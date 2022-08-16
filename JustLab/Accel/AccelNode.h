#pragma once

#include <vector>
#include "Global.h"
#include "Hittable/Bounds.h"

namespace Just{
    struct AccelNode
    {
        size_t child;
        Bounds3f bbox;
        std::vector<std::pair<size_t,size_t>> indexes;

        AccelNode() : bbox(), child(0) {}

        explicit AccelNode(const Bounds3f& bbox) : bbox(bbox), child(0) {}

        AccelNode(const Bounds3f& bbox, size_t size)
                : bbox(bbox), indexes(size), child(0) {}
    };
}