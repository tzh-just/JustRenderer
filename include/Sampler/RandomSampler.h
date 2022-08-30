#pragma once

#include "Core/Sampler.h"

namespace Just {
    struct RandomSampler : public Sampler {

        explicit RandomSampler(int spp) : Sampler(spp) {}

        std::tuple<float, float> Sample(float i, float j) override;
    };
}