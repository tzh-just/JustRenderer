#pragma once

#include <random>

namespace Just {
    class RNG {
    public:
        explicit RNG() : rngEngine(rd()) {}

        float Random() {
            return uniform(rngEngine);
        }

        float Random(float min, float max) {
            return min + (max - min) * uniform(rngEngine);
        }

    private:
        std::random_device rd;
        std::mt19937_64 rngEngine;
        std::uniform_real_distribution<float> uniform{0.0f,1.0f};
    };
}
