#pragma once

#include "Just/Math/Vector.h"

namespace Just {
    template<size_t N, typename T>
    struct Bounds {
        Vector<N, T> min;
        Vector<N, T> max;

        Bounds(const Vector<N, T> &min_, const Vector<N, T> &max_) : min(min_), max(max_) {}
    };
}