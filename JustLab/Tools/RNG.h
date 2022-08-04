//================================================
// 随机数生成器
//================================================

#pragma once

#include <random>

namespace Just
{

    template<typename T>
    class RNG
    {
    public:
        explicit RNG(int seed = 1234) : rngEngine(seed) {}

        constexpr T Random(T min, T max)
        {
            return min + (max - min) * uniform(rngEngine);
        }

    private:
        std::mt19937_64 rngEngine;
        std::uniform_real_distribution<float> uniform;
    };

    using RandomFloat = RNG<float>;
    using RandomInt = RNG<int>;

}
