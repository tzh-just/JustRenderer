#pragma once

#include "Global.h"
#include "Math/Color3.h"
#include "Geometry/Ray.h"
#include "Scene.h"
#include "Sampler.h"
#include "Camera.h"

namespace Just {
    struct Integrator {
        virtual void Render(std::shared_ptr<Scene> scene) = 0;
    };

    struct SamplerIntegrator : public Integrator {
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Sampler> sampler;
        std::shared_ptr<Film> film;
        std::shared_ptr<Scene> scene;

        SamplerIntegrator(std::shared_ptr<Camera> camera,
                          std::shared_ptr<Sampler> sampler,
                          std::shared_ptr<Film> film,
                          std::shared_ptr<Scene> scene)
                : camera(camera), sampler(sampler), film(film), scene(scene) {}

        virtual Spectrum Li(const Ray3f& ray) const = 0;

        void Render(std::shared_ptr<Scene> scene) override;
    };
}