#pragma once

#include "Core/Sampler.h"

namespace Just {
    struct TrapezoidalSampler : public Sampler {

        explicit TrapezoidalSampler(int spp) : Sampler(spp), subIndex(0) {}

        int subIndex;

        void TrapezoidalSampler::StartPixel() {
            Sampler::StartPixel();
            subIndex = 0;
        }

        bool TrapezoidalSampler::StartNextPixel() {
            //更新子像素索引和总索引
            if (subIndex >= 4) {
                subIndex = 0;
                index++;
            }
            subIndex++;
            return index <= spp;
        }

        std::tuple<float, float> TrapezoidalSampler::Sample(float i, float j) {
            subIndex++;

            //子像素位置
            auto sx = index % 2;
            auto sy = index / 2;

            //梯形分布
            float r1 = 2 * rng.UniformFloat();
            float r2 = 2 * rng.UniformFloat();
            float dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
            float dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

            return {i + (dx + float(sx) + 0.5f) / 2.0f, j + (dy + float(sy) + 0.5f) / 2.0f};
        }
    };
}