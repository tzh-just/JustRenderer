#include "Sampler.h"

namespace Just {

    void Sampler::StartPixel() {
        index = 0;
    }

    bool Sampler::StartNextPixel() {
        return ++index < spp;
    }

    float Sampler::Get1D() {
        return rng.UniformFloat();
    }

    Point2f Sampler::Get2D() {
        return {rng.UniformFloat(), rng.UniformFloat()};
    }

}