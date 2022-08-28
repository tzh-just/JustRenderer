#pragma once

#include "Math/Vector3.h"

namespace Just {
    struct Emitter {
        Vector3f radiance;

        virtual float PDF() const = 0;

        virtual Vector3f Sample() const = 0;

        virtual Vector3f Eval() const = 0;
    };
}