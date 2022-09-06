#pragma once

#include "Core/Accel.h"

namespace Just {
class Naive : public Accel {
public:
    Naive() : Accel(1, 0) {}

    void Divide(size_t nodeIndex, std::vector<AccelNode>& children) override;

    void Traverse(const Ray& ray, size_t nodeIndex, std::queue<size_t>& queue) const override;
};

void Naive::Divide(size_t nodeIndex, std::vector<AccelNode>& children) {}

void Naive::Traverse(const Ray& ray, size_t nodeIndex, std::queue<size_t>& queue) const {}
}