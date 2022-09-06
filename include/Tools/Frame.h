#pragma once

#include "Math/Vector.h"

namespace Just {
struct Frame {
    Vector3f s, t, n;

    Frame() = default;

    explicit Frame(const Vector3f& n) : n(n) {
        CoordinateSystem(n, s, t);
    }

    Frame(const Vector3f& s, const Vector3f& t, const Vector3f& n) : s(s), t(t), n(n) {}

    Vector3f ToLocal(const Vector3f& v) const {
        return {Dot(v, s), Dot(v, t), Dot(v, n)};
    }

    Vector3f ToWorld(const Vector3f& v) const {
        return s * v.x + t * v.y + n * v.z;
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

    static void CoordinateSystem(const Vector3f& v1, Vector3f& v2, Vector3f& v3) {
        if (std::abs(v1.x) > std::abs(v1.y)) {
            float invLen = 1.0f / std::sqrt(v1.x * v1.x + v1.z * v1.z);
            v2 = Vector3f(-v1.z * invLen, 0.0f, v1.x * invLen);
        } else {
            float invLen = 1.0f / std::sqrt(v1.y * v1.y + v1.z * v1.z);
            v2 = Vector3f(0.0f, v1.z * invLen, -v1.y * invLen);
        }
        v3 = Cross(v1, v2);
    }
};
}