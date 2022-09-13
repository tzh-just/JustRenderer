#pragma once

#include "Core/Integrator.h"

namespace Just {
struct NormalsIntegrator : public SamplerIntegrator {
    NormalsIntegrator(std::shared_ptr<Camera> camera, std::shared_ptr<Sampler> sampler, std::shared_ptr<Film> film)
            : SamplerIntegrator(camera, sampler, film) {}

    Spectrum Li(const Ray& ray, std::shared_ptr<Scene> scene) const override;
};

Spectrum NormalsIntegrator::Li(const Ray& ray, std::shared_ptr<Scene> scene) const {
    //射线相交测试
    HitRecord record;
    if (!scene->RayIntersect(ray, record)) {
        return Spectrum(0.0f);
    }
    Vector3f normal = Abs(record.shadingFrame.n);
    return {normal.x, normal.y, normal.z};
}
}