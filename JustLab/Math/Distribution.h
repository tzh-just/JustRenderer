#pragma once

#include "VectorExt.h"

namespace Just {
    //正方形均匀采样
    Vector2f SamplingUniformSquare(const Vector2f &sample) {
        return sample;
    }

    float SamplingUniformSquarePdf(const Vector2f &sample) {
        return 1;
    }

    //帐篷均匀采样
    Vector2f SamplingTent(const Vector2f &sample) {
        auto x = sample.x < 0.5f ? sqrt(2 * sample.x) - 1 : 1 - sqrt(2 - 2 * sample.x);
        auto y = sample.y < 0.5f ? sqrt(2 * sample.y) - 1 : 1 - sqrt(2 - 2 * sample.y);
        return {x, y};
    }

    float SamplingTentPdf(const Vector2f &p) {
        bool x = p.x >= -1 && p.x <= 1;
        bool y = p.y >= -1 && p.y <= 1;

        return x && y ? (1 - abs(p.x)) * (1 - abs(p.y)) : 0;
    }

    //圆盘均匀采样
    Vector2f SamplingUniformDisk(const Vector2f &sample) {
        auto radius = sqrt(sample.x);
        auto angle = sample.y * M_PI * 2;
        return {radius * cos(angle), radius * sin(angle)};
    }

    float SamplingUniformDiskPdf(const Vector2f &p) {
        return sqrt(p.x * p.x + p.y * p.y) <= 1 ? INV_PI : 0.0f;
    }

    //球体表面均匀采样
    Vector3f SamplingUniformSphere(const Vector2f &sample) {
        auto phi = sample.x * M_PI * 2;
        auto theta = acos(1 - 2 * sample.y);
        return {sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta)};
    }

    float SamplingUniformSpherePdf(const Vector3f &v) {
        return INV_PI4;
    }

    //半球均匀采样
    Vector3f SamplingUniformHemisphere(const Vector2f &sample) {
        auto phi = sample.x * M_PI * 2;
        auto theta = acos(1 - sample.y);
        return {sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta)};
    }

    float SamplingUniformHemispherePdf(const Vector3f &v) {
        return v.z >= 0 ? INV_PI4 : 0;
    }

    //cosine-weight 半球采样
    Vector3f SamplingCosineHemisphere(const Vector2f &sample) {
        auto d = SamplingUniformDisk(sample);
        return {d.x, d.y, sqrt(1 - d.x * d.x - d.y * d.y)};
    }

    float SamplingCosineHemispherePdf(const Vector3f &v) {
        return v.z >= 0 ? v.z * INV_PI : 0;
    }
}