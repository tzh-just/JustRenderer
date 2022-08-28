#pragma once

#include "Geometry/Vector3.h"
#include "Geometry/Ray.h"

namespace Just {
    struct Integrator {
        Integrator() = default;

        ~Integrator() = default;

        virtual Vector3f Li() const = 0;
    };
}