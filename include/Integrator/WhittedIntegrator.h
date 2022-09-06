#pragma once

#include "Core/Integrator.h"

namespace Just {
struct WhittedIntegrator : public SamplerIntegrator {
    WhittedIntegrator(std::shared_ptr<Camera> camera, std::shared_ptr<Sampler> sampler, std::shared_ptr<Film> film)
            : SamplerIntegrator(camera, sampler, film) {}

    Spectrum Li(const Ray3f& ray, std::shared_ptr<Scene> scene) const override;
};

Spectrum WhittedIntegrator::Li(const Ray3f& ray, std::shared_ptr<Scene> scene) const {
    //射线相交测试
    HitRecord record;
    if (!scene->RayIntersect(ray, record)) {
        return Spectrum(0.0f);
    }
    Spectrum normal = Abs(record.shadingFrame.n);
    return normal;
}
}