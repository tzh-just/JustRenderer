#pragma once

#include "Core/Sampler.h"

namespace Just {
    struct TrapezoidalSampler : public Sampler {

        explicit TrapezoidalSampler(int spp) : Sampler(spp), subIndex(0) {}

        int subIndex;

        void StartPixel() override;

        bool StartNextPixel() override;

        std::tuple<float, float> Sample(float i, float j) override;
    };
}