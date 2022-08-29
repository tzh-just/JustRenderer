#pragma once

#include "Core/Light.h"

namespace Just {
    struct AreaLight : Light {
        Vector3f Sample() const override;

        Vector3f Eval() const override;

        float PDF() const override;
    };
}