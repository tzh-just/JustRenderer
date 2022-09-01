#pragma once

#include "Core/Integrator.h"

namespace Just {
    struct WhittedIntegrator : public SamplerIntegrator {
        WhittedIntegrator(std::shared_ptr<Camera> camera, std::shared_ptr<Sampler> sampler, std::shared_ptr<Film> film)
                : SamplerIntegrator(camera, sampler, film, std::shared_ptr<Scene>()) {}

        Spectrum Li(const Ray3f& ray) const override;
    };
}