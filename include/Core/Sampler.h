#pragma once

#include "Math/Point2.h"

namespace Just {
    struct Sampler {
        Point2i curPixel;
        int64_t currPixelIndex;
        size_t offset1D;
        size_t offset2D;

        virtual float Get1D() = 0;

        virtual Point2f Get2D() = 0;

        virtual void StartPixel(const Point2i& p);

        virtual bool StartNextPixel(int64_t i);
    };

    void Sampler::StartPixel(const Point2i& p) {

    }
}