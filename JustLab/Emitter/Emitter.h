#pragma once

#include "Math/Vector.h"

namespace Just{
    struct Emitter{
        Vector3f radiance;

        virtual float PDF() const = 0;
        virtual Vector3f Sample() const = 0;
        virtual Vector3f Eval() const = 0;
    };

    struct AreaLight : public Emitter{
        float PDF() const override {

        }
        Vector3f Sample() const override{

        }
        Vector3f Eval() const override{

        }
    };
}