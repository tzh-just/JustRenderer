#pragma once

#include "Core/Sampler.h"

namespace Just {
    struct RandomSampler : public Sampler {

        explicit RandomSampler(int spp) : Sampler(spp) {}

        std::tuple<float, float> Sample(float i, float j) override {
            //随机偏移点坐标
            return {i + Get1D(), j + Get1D()};
        }
    };
}