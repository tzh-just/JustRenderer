#pragma once

#include "Core/Emitter.h"

namespace Just {
    struct AreaLight : Emitter {
        Vector3f Sample() const override;

        Vector3f Eval() const override;

        float PDF() const override;
    };
}