#pragma once

#include "Math/Vector3.h"

namespace Just {
    struct Frame {
        Vector3f s, t, n;


        Frame(const Vector3f& s, const Vector3f& t, const Vector3f& n) : s(s), t(t), n(n) {}

        Vector3f ToLocal(const Vector3f& v) const {
            return {Dot(v, s), Dot(v, t), Dot(v, n)};
        }

        Vector3f ToWorld(const Vector3f& v) const {
            return {Dot(v, s), Dot(v, t), Dot(v, n)};
        }
    };

    inline void CoordinateSystem(const Vector3f& v, Vector3f& other1, Vector3f& other2) {
        if (std::abs(v.x) > std::abs(v.y)) {
            float invLength = 1.0f / std::sqrt(v.x * v.x + v.z * v.z);
            other2 = Vector3f(v.z * invLength, 0.0f, -v.x * invLength);
        } else {
            float invLength = 1.0f / std::sqrt(v.y * v.y + v.z * v.z);
            other1 = Vector3f(0.0f, v.z * invLength, -v.y * invLength);
        }
    }

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