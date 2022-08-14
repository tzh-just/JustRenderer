#pragma once

#include <Math/Vector3.h>

namespace Just{
    struct Emitter{
        Vector3 radiance;

        virtual float PDF() const = 0;
        virtual Vector3 Sample() const = 0;
        virtual Vector3 Eval() const = 0;
    };

    struct AreaLight : public Emitter{
        float PDF() const override {

        }
        Vector3 Sample() const override{

        }
        Vector3 Eval() const override{

        }
    };
}