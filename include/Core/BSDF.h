#pragma once

#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Math/Color3.h"
#include "Tools/Frame.h"
#include "Shape/Mesh.h"
#include "Fresnel.h"

namespace Just {
//ref: mitsuba
enum BSDFType {
    None = 1 << 0,
    Diffuse = 1 << 1,
    Glossy = 1 << 2,
    Delta = 1 << 3,
    ALL = Diffuse | Glossy | Delta
};

//ref: mitsuba
struct BSDFRecord {
    //入射方向
    Vector3f wi;
    Vector3f wo;
    float pdf;
    float eta;
    BSDFType type;

    explicit BSDFRecord(const Vector3f& wi) : wi(wi), pdf(0.0f), eta(1.0f), type(BSDFType::None) {}
};

//ref: mitsuba
struct BSDF {
    const BSDFType type;

    explicit BSDF(BSDFType type) : type(type) {}

    bool IsMatched(BSDFType t) const {
        return (type & t) == type;
    }

    virtual Spectrum Eval(const BSDFRecord& record) const = 0;

    virtual Spectrum Sample(BSDFRecord& record, const Point2f& sample) const = 0;

    virtual float Pdf(const BSDFRecord& record) const = 0;
};

//反射
inline Vector3f Reflect(const Vector3f& wo, const Vector3f& n) {
    return -wo + 2.0f * Dot(wo, n) * n;
}

struct SpecularReflection : public BSDF {
    Spectrum R;
    Fresnel* fresnel;

    SpecularReflection(const Spectrum& R, Fresnel* fresnel)
            : BSDF(BSDFType::Delta), R(R), fresnel(fresnel) {}

    //除了完美反射方向，镜面反射不会反射到任何方向
    Spectrum Eval(const BSDFRecord& record) const override {
        return Spectrum(0.0f);
    }

    Spectrum Sample(BSDFRecord& record, const Point2f& sample) const override {
        //z轴向上的局部坐标系中，反射可以简化计算
        record.wi = Vector3f(-record.wo.x, -record.wo.y, record.wo.z);
        record.pdf = 1.0f;
        return fresnel->Eval(Frame::CosTheta(record.wi)) * R / Frame::AbsCosTheta(record.wi);
    }

    float Pdf(const BSDFRecord& record) const override {
        return 0.0f;
    }
};

}