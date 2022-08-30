#pragma once

#include "Global.h"
#include "Math/Vector3.h"
#include "Geometry/Ray.h"
#include "Core/Scene.h"

namespace Just {
    struct Integrator {
        virtual void Render(const Scene& scene) = 0;
    };

    struct SamplerIntegrator: public Integrator{
        std::shared_ptr<Camera> camera;
        virtual Vector3f Li() const = 0;
        void Render(const Scene& scene) override;
    };
}