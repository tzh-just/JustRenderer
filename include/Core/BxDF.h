#pragma once

#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Math/Color3.h"

namespace Just {
    struct BxDFRecord {

    };
    struct BxDF {

        virtual Spectrum F(const Vector3f &wo, const Vector3f &wi) const = 0;
        virtual Spectrum SampleF(const Vector3f &wo, Vector3f *wi, float *pdf, BxDFRecord *record) const = 0;
        virtual float Pdf() const = 0;
    };
}