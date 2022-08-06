#pragma once

#include <Light/ILight.h>

namespace Just{
    struct AreaLight : public ILight{
        float Pdf() const override {

        }
        Vector3 Sample() const override{

        }
        Vector3 eval() const override{

        }
    };
}