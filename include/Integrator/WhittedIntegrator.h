#pragma once

#include "Core/Integrator.h"

namespace Just {
    struct WhittedIntegrator : public Integrator {
        Vector3f Li() const override;
        void Render(const Scene& scene) override;
    };
}