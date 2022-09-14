#pragma once

#include "Core/Integrator.h"
#include "Math/Point3.h"
#include "Math/Color3.h"
#include "Tools/Warp.h"

namespace Just {
//Material Sample Integrator
struct MatsIntegrator : public SamplerIntegrator {
    MatsIntegrator(std::shared_ptr<Camera> camera, std::shared_ptr<Sampler> sampler, std::shared_ptr<Film> film)
            : SamplerIntegrator(camera, sampler, film) {}

    Spectrum Li(const Ray& ray, std::shared_ptr<Scene> scene) const override;

    int maxDepth = 10;
};

Spectrum MatsIntegrator::Li(const Ray& ray, std::shared_ptr<Scene> scene) const {
    int depth = 1;
    float probability = 0.0f;
    Spectrum coefficient(1.0f), radiance(0.0f);
    while (depth < maxDepth) {
        HitRecord record;
        if (!scene->RayIntersect(ray, record)) {
            break;
        }


    }
}
}