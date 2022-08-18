#pragma once

#include <vector>
#include "Global.h"
#include "Geometry/Bounds3.h"

namespace Just {
    struct AccelNode {
        int child;
        Bounds3f bbox;
        std::vector<std::pair<int, int>> indexes;

        AccelNode() : bbox(), child(0) {}

        explicit AccelNode(const Bounds3f& bbox) : bbox(bbox), child(0) {}

        AccelNode(const Bounds3f& bbox, int size)
                : bbox(bbox), indexes(size), child(0) {}
    };
}