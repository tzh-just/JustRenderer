//================================================
// 积分器抽象类
//================================================

#pragma once

#include "Math/Vector.h"
#include "Math/Color.h"

namespace Just
{
    struct Integrator
    {
        Integrator() = default;

        ~Integrator() = default;

        virtual Color3f Li() const = 0;
    };
}