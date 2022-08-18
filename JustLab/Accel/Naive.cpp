#pragma once

#include "Accel/Accel.h"

namespace Just {
    void Naive::Divide(int nodeIndex, std::vector<AccelNode>* children) {
        return;
    }

    bool Naive::Traverse(Ray* ray, HitRecord* record, bool isShadowRay) const {
        //暴力遍历所有图元进行相交测试
    }
}