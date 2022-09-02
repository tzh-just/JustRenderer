#pragma once

#include "Math/Vector.h"


namespace Just {

    //正方形均匀采样
    Point2f SamplingUniformSquare(const Point2f& point) {
        return point;
    }

    float SamplingUniformSquarePdf(const Point2f& point) {
        return 1;
    }

    //帐篷均匀采样
    Point2f SamplingTent(const Point2f& point) {
        auto x = point.x < 0.5f ? sqrt(2 * point.x) - 1 : 1 - sqrt(2 - 2 * point.x);
        auto y = point.y < 0.5f ? sqrt(2 * point.y) - 1 : 1 - sqrt(2 - 2 * point.y);
        return {x, y};
    }

    float SamplingTentPdf(const Point2f& point) {
        bool x = point.x >= -1 && point.x <= 1;
        bool y = point.y >= -1 && point.y <= 1;

        return x && y ? (1 - abs(point.x)) * (1 - abs(point.y)) : 0;
    }

    //圆盘均匀采样
    Point2f SamplingUniformDisk(const Point2f& point) {
        auto radius = sqrt(point.x);
        auto angle = point.y * kPI * 2;
        return {radius * cos(angle), radius * sin(angle)};
    }

    float SamplingUniformDiskPdf(const Point2f& p) {
        return sqrt(p.x * p.x + p.y * p.y) <= 1 ? kInvPI : 0.0f;
    }

    //球体表面均匀采样
    Vector3f SamplingUniformSphere(const Point2f& point) {
        auto phi = point.x * kPI * 2;
        auto theta = acos(1 - 2 * point.y);
        return {sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta)};
    }

    float SamplingUniformSpherePdf(const Vector3f& v) {
        return kInv4PI;
    }

    //半球均匀采样
    Vector3f SamplingUniformHemisphere(const Point2f& point) {
        auto phi = point.x * kPI * 2;
        auto theta = acos(1 - point.y);
        return {sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta)};
    }

    float SamplingUniformHemispherePdf(const Vector3f& v) {
        return v.z >= 0 ? kInv4PI : 0;
    }

    //cosine-weight 半球采样
    Vector3f SamplingCosineHemisphere(const Point2f& point) {
        auto d = SamplingUniformDisk(point);
        return {d.x, d.y, sqrt(1 - d.x * d.x - d.y * d.y)};
    }

    float SamplingCosineHemispherePdf(const Vector3f& v) {
        return v.z >= 0 ? v.z * kInvPI : 0;
    }

}