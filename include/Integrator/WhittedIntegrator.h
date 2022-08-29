#pragma once

#include "Core/Integrator.h"

namespace Just {
    struct WhittedIntegrator : Integrator {
        Vector3f Li() const override;
    };
}