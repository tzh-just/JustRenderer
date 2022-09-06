#pragma once

#include "Core/Sampler.h"

namespace Just {
struct IndependentSampler : public Sampler {

    explicit IndependentSampler(int spp) : Sampler(spp) {}

    std::tuple<float, float> Sample(float i, float j) override {
        //随机偏移点坐标
        return {i , j};
    }
};
}