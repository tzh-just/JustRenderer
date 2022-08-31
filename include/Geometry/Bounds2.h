#pragma once

#include "Global.h"
#include "Math/Point2.h"
#include "Ray.h"

namespace Just {
    template<typename T>
    struct Bounds2 {
        Point2<T> pMin, pMax;

        Bounds2() : pMin(std::numeric_limits<T>::max()), pMax(std::numeric_limits<T>::lowest()) {}

        explicit Bounds2(const Point2<T>& p) : pMin(p), pMax(p) {}

        Bounds2(const Point2f& p1, const Point2f& p2)
                : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
                  pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y)) {}

        static bool Inside(const Point2<T>& p, const Bounds2<T>& b);

        static bool InsideExclusive(const Point2<T>& p, const Bounds2<T>& b);
    };



    using Bounds2f = Bounds2<float>;
    using Bounds2i = Bounds2<int>;
}