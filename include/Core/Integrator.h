#pragma once

#include "Global.h"
#include "Math/Vector3.h"
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

        SamplerIntegrator(std::shared_ptr<Camera> camera, std::shared_ptr<Sampler> sampler)
            : camera(camera), sampler(sampler) {}

        virtual Vector3f Li() const = 0;

        void Render(std::shared_ptr<Scene> scene) override;
    };
}