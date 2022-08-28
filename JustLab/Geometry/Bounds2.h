#pragma once

#include "Global.h"
#include "Math/Point2.h"
#include "Ray.h"

namespace Just {
    template<typename T>
    struct Bounds2 {
        Point2<T> pMin, pMax;

        Bounds2() {
            T minNum = std::numeric_limits<T>::lowest();
            T maxNum = std::numeric_limits<T>::max();
            pMin = Point2<T>(maxNum, maxNum, maxNum);
            pMax = Point2<T>(minNum, minNum, minNum);
        }

        explicit Bounds2(const Point2<T>& p) : pMin(p), pMax(p) {}

        Bounds2(const Point2f& p1, const Point2f& p2)
                : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
                  pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y)) {}
    };

    template<typename T>
    bool Inside(const Point2<T>& p, const Bounds2<T>& b) {
        return p.x >= b.pMin.x && p.x <= b.pMax.x &&
               p.y >= b.pMin.y && p.y <= b.pMax.y;
    }

    //检测点则框内：不包括边界上的点
    template<typename T>
    bool InsideExclusive(const Point2<T>& p, const Bounds2<T>& b) {
        return p.x >= b.pMin.x && p.x < b.pMax.x &&
               p.y >= b.pMin.y && p.y < b.pMax.y;
    }

    using Bounds2f = Bounds2<float>;
}