//================================================
// 积分器抽象类
//================================================

#pragma once

#include "Math/Vector.h"

namespace Just
{
    struct Integrator
    {
        Integrator() = default;

        ~Integrator() = default;

        virtual Vector3f Li() const = 0;
    };
}