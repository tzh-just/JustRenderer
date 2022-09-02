#pragma once

#include "Core/Integrator.h"

namespace Just {
struct WhittedIntegrator : public SamplerIntegrator {
    WhittedIntegrator(std::shared_ptr<Camera> camera, std::shared_ptr<Sampler> sampler, std::shared_ptr<Film> film)
            : SamplerIntegrator(camera, sampler, film, std::shared_ptr<Scene>()) {}

    Spectrum Li(const Ray3f& ray) const override;
};

Spectrum WhittedIntegrator::Li(const Ray3f& ray) const {
    //射线相交测试
    HitRecord record;
    if (!scene->RayIntersect(ray, record)) {
        return Spectrum(0.0f);
    }
    return {1.0f, 1.0f, 1.0f};
}
}