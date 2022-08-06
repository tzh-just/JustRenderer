#pragma once

#include <Math/Vector3.h>

namespace Just{
    struct ILight{
        Vector3 radiance;

        virtual float Pdf() const = 0;
        virtual Vector3 Sample() const = 0;
        virtual Vector3 eval() const = 0;
    };
}