#pragma once

#include "Core/Light.h"

namespace Just {
struct AreaLight : Light {
    Vector3f AreaLight::Sample() const {
        return {0, 0, 0};
    }

    Vector3f AreaLight::Eval() const {
        return {0, 0, 0};
    }

    float AreaLight::PDF() const {
        return 0;
    }
};


}