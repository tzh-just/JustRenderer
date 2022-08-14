//================================================
// 本地坐标系的快速计算
//================================================

#pragma once

#include "Math/Vector3.h"

namespace Just
{
    struct Frame
    {
        Vector3f s, t, n;

        constexpr Frame() {}

        constexpr Frame(const Vector3f& n) : n(n) {}

        constexpr Frame(const Vector3f& s, const Vector3f& t, const Vector3f n) : s(s), t(t), n(n) {}

        constexpr Vector3f ToLocal(const Vector3f& v) const
        {

        }

        constexpr Vector3f ToWorld() const
        {

        }
    };

    constexpr float CosTheta(const Vector3f& v)
    {
        return v.z;
    }

    constexpr float SinTheta2(const Vector3f& v)
    {
        return 1 - v.z * v.z;
    }

    constexpr float SinTheta(const Vector3f& v)
    {
        float temp = SinTheta2(v);
        return temp <= 0.0f ? 0.0f : std::sqrt(temp);
    }

    constexpr float TanTheta(const Vector3f& v)
    {
        float temp = SinTheta2(v);
        return temp <= 0.0f ? 0.0f : std::sqrt(temp) / v.z;
    }
}