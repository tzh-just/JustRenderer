#pragma once

#include "Core/Accel.h"

namespace Just {
    class Naive : public Accel {
    public:
        Naive() : Accel(16, 1) {}

        void Divide(size_t nodeIndex, std::vector<AccelNode>* children) override;

        bool Traverse(const Ray3f& ray, HitRecord& record, bool isShadowRay) const override;
    };
}