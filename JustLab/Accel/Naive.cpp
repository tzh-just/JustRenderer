#pragma once

#include "Accel/Accel.h"

namespace Just {
    void Naive::Divide(size_t nodeIndex, std::vector<AccelNode>* children) {

    }

    bool Naive::Traverse(Ray* ray, HitRecord* record, bool isShadowRay) const {
        //暴力遍历所有图元进行相交测试
    }
}