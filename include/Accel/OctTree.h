#pragma once

#include "Core/Accel.h"

namespace Just {
    class OctTree : public Accel {
    public:
        OctTree() : Accel(16, 12) {}

        void Divide(size_t nodeIndex, std::vector<AccelNode>* children) override;

        bool Traverse(const Ray& ray, HitRecord& record, bool isShadowRay) const override;
    };
}