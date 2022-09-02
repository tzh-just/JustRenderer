#pragma once

#include "Vector.h"

namespace Just {
//角度和弧度互转
inline float Radians(float deg) {
    return kPI / 180.0f * deg;
}

inline float Degrees(float rad) {
    return 180.0f / kPI * rad;
}

//RGB和光谱转换
static Spectrum RGB2Spectrum(const Color3i& rgb) {
    return {
            std::clamp(float(rgb.r) / 255.0f, 0.0f, 1.0f),
            std::clamp(float(rgb.g) / 255.0f, 0.0f, 1.0f),
            std::clamp(float(rgb.b) / 255.0f, 0.0f, 1.0f)
    };
}

static Color3i Spectrum2RGB(const Spectrum& spectrum) {
    return {
            std::clamp(int(spectrum.r * 255), 0, 255),
            std::clamp(int(spectrum.g * 255), 0, 255),
            std::clamp(int(spectrum.b * 255), 0, 255)
    };
}
}