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

        static float CosTheta(const Vector3f& v) { return v.z; }

        static float SinTheta2(const Vector3f& v) { return 1 - v.z * v.z; }

        static float SinTheta(const Vector3f& v) {
            float temp = SinTheta2(v);
            return temp <= 0.0f ? 0.0f : std::sqrt(temp);
        }

        static float TanTheta(const Vector3f& v) {
            float temp = SinTheta2(v);
            return temp <= 0.0f ? 0.0f : std::sqrt(temp) / v.z;
        }

        static void CoordinateSystem(const Vector3f& v, Vector3f& other1, Vector3f& other2);
    };
}