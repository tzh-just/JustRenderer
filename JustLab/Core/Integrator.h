#pragma once

#include "Geometry/Vector3.h"

namespace Just {
    struct Integrator {
        Integrator() = default;

        ~Integrator() = default;

        virtual Vector3 Li() const = 0;
    };
}