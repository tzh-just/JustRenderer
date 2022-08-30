#include "RandomSampler.h"

namespace Just {
    std::tuple<float, float> RandomSampler::Sample(float i, float j) {
        //随机偏移点坐标
        return {i + Get1D(), j + Get1D()};
    }
}