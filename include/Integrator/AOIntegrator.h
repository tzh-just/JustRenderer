#pragma once

#include "Core/Integrator.h"
#include "Math/Point3.h"
#include "Math/Color3.h"
#include "Tools/Warp.h"

namespace Just {
struct AOIntegrator : public SamplerIntegrator {
    AOIntegrator(std::shared_ptr<Camera> camera, std::shared_ptr<Sampler> sampler, std::shared_ptr<Film> film)
            : SamplerIntegrator(camera, sampler, film) {}

    Spectrum Li(const Ray& ray, std::shared_ptr<Scene> scene) const override;
};

Spectrum AOIntegrator::Li(const Ray& ray, std::shared_ptr<Scene> scene) const {
    //射线相交测试
    HitRecord record;
    if (!scene->RayIntersect(ray, record)) {
        return Spectrum(0.0f);
    }

    Vector3f dir = Warp::SquareToCosineHemisphere(sampler->Get2D());
    float pdf = Warp::SquareToCosineHemispherePdf(dir);

    dir = record.shadingFrame.ToWorld(dir);

    if (scene->RayIntersect(Ray(record.point + dir * kEpsilon, dir))) {
        return Spectrum(0.0f);
    }

    auto cosTheta = std::max(0.0f, Dot(record.shadingFrame.n, (Normalize(dir))));
    //Li/pi * cos_theta / pdf
    return Spectrum(1.0f) * kInvPI * cosTheta / pdf;
}
}