#pragma once

#include "Core/Integrator.h"

namespace Just {
    struct WhittedIntegrator : public SamplerIntegrator {
        Vector3f Li() const override;
    };
}