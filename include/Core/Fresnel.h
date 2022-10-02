#pragma once


#include "Math/Color3.h"

namespace Just{

//ref: pbrt-v3
//电介质菲涅尔
float FrDielectric(float cosThetaI, float etaI, float etaT) {
    //限制溢出
    cosThetaI = Clamp(cosThetaI, -1.0f, 1.0f);
    //相反则调换折射率
    if (cosThetaI <= 0.0f) {
        std::swap(etaI, etaT);
        cosThetaI = std::abs(cosThetaI);
    }
    float sinThetaI = std::sqrt(std::max(1 - cosThetaI * cosThetaI, 0.0f));
    float sinThetaT = etaI / etaT * sinThetaI;
    //全反射
    if (sinThetaT >= 1.0f) {
        return 1.0f;
    }
    float cosThetaT = std::sqrt(std::max(1 - sinThetaT * sinThetaT, 0.0f));
    float Rpral = (etaT * cosThetaI - etaI * cosThetaT) /
                  (etaT * cosThetaI + etaI * cosThetaT);
    float Rprap = (etaI * cosThetaI - etaT * cosThetaT) /
                  (etaI * cosThetaI + etaT * cosThetaT);

    return (Rpral * Rpral + Rprap * Rprap) / 2;
}

//ref: pbrt-v3
//导体菲涅尔
Spectrum FrConductor(float cosThetaI, const Spectrum& etaI, const Spectrum& etaT, const Spectrum& k) {
    cosThetaI = Clamp(cosThetaI, -1.0f, 1.0f);
    Spectrum eta = etaT / etaI;
    Spectrum etak = k / etaI;

    float cosThetaI2 = cosThetaI * cosThetaI;
    float sinThetaI2 = 1 - cosThetaI2;
    Spectrum eta2 = eta * eta;
    Spectrum etak2 = etak * etak;

    Spectrum t0 = eta2 - etak2 - sinThetaI2;
    Spectrum a2plusb2 = Sqrt(t0 * t0 + 4 * eta2 * etak2);
    Spectrum t1 = a2plusb2 + cosThetaI2;
    Spectrum a = Sqrt(0.5f * (a2plusb2 + t0));
    Spectrum t2 = 2 * cosThetaI * a;
    Spectrum Rs = (t1 - t2) / (t1 + t2);

    Spectrum t3 = cosThetaI2 * a2plusb2 + sinThetaI2 * sinThetaI2;
    Spectrum t4 = t2 * sinThetaI2;
    Spectrum Rp = Rs * (t3 - t4) / (t3 + t4);

    return 0.5f * (Rp + Rs);
}


struct Fresnel {
    virtual Spectrum Eval(float cosThetaI) const = 0;
};

struct FresnelConductor : public Fresnel {
    Spectrum etaI;
    Spectrum etaT;
    Spectrum k;

    FresnelConductor(const Spectrum& etaI, const Spectrum& etaT, const Spectrum& k)
            : etaI(etaI), etaT(etaT), k(k) {}

    Spectrum Eval(float cosThetaI) const override {
        return FrConductor(std::abs(cosThetaI), etaI, etaT, k);
    }
};

struct FresnelDielectric : public Fresnel {
    float etaI;
    float etaT;

    FresnelDielectric(float etaI, float etaT) : etaI(etaI), etaT(etaT) {}

    Spectrum Eval(float cosThetaI) const override {
        float fr = FrDielectric(cosThetaI, etaI, etaT);
        return {fr, fr, fr};
    }
};

struct FresnelNoOp : public Fresnel {
    Spectrum Eval(float cosThetaI) const override {
        return Spectrum(1.0f);
    }
};
}