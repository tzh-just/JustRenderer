#pragma once

#include "Core/Light.h"

namespace Just {
    struct AreaLight : Light {
        Vector3f AreaLight::Sample() const {}

        Vector3f AreaLight::Eval() const {}

        float AreaLight::PDF() const {}
    };


}