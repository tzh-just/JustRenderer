#pragma once

#include "Math/Vector3.h"

namespace Just {
    struct Frame {
        Vector3f x, y, z;

    };

    inline float CosTheta(const Vector3f& v) {
        return v.z;
    }

    inline float SinTheta2(const Vector3f& v) {
        return 1 - v.z * v.z;
    }

    inline float SinTheta(const Vector3f& v) {
        float temp = SinTheta2(v);
        return temp <= 0.0f ? 0.0f : std::sqrt(temp);
    }

    inline float TanTheta(const Vector3f& v) {
        float temp = SinTheta2(v);
        return temp <= 0.0f ? 0.0f : std::sqrt(temp) / v.z;
    }
}