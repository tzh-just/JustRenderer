#pragma once

#include "Core/Accel.h"

namespace Just {
class NaiveAccel : public Accel {
public:
    NaiveAccel() : Accel(1, 0) {}

    void Divide(size_t nodeIndex, std::vector<AccelNode>& children) override;

    void Traverse(const Ray& ray, size_t nodeIndex, std::queue<size_t>& queue) const override;
};

void NaiveAccel::Divide(size_t nodeIndex, std::vector<AccelNode>& children) {}

void NaiveAccel::Traverse(const Ray& ray, size_t nodeIndex, std::queue<size_t>& queue) const {}
}