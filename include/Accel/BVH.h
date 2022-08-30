#pragma once

#include "Core/Accel.h"

namespace Just {
    class BVH : public Accel {
    protected:
        const int kNumBuckets = 10;

    public:
        BVH() : Accel(16, 32) {}

        void Divide(size_t nodeIndex, std::vector<AccelNode>* children) override;

        bool Traverse(Ray* ray, HitRecord* record, bool shadow) const override;
    };

}