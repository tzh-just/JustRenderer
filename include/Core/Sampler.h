#pragma once

#include <tuple>
#include <Math/Vector.h>
#include "Tools/RNG.h"

namespace Just {

    struct Sampler {
        int spp;
        int index;

        RNG rng;

        explicit Sampler(int spp) : spp(spp), index(0) {}

        virtual std::tuple<float, float> Sample(float i, float j) = 0;

        virtual float Get1D();

        virtual Point2f Get2D();

        virtual void StartPixel();

        virtual bool StartNextPixel();
    };

}