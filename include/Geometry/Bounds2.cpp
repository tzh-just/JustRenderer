#include "Bounds2.h"

namespace Just{
    template<typename T>
    bool Bounds2<T>::Inside(const Point2<T>& p, const Bounds2<T>& b) {
        return p.x >= b.pMin.x && p.x <= b.pMax.x &&
               p.y >= b.pMin.y && p.y <= b.pMax.y;
    }

    //检测点则框内：不包括边界上的点
    template<typename T>
    bool Bounds2<T>::InsideExclusive(const Point2<T>& p, const Bounds2<T>& b) {
        return p.x >= b.pMin.x && p.x < b.pMax.x &&
               p.y >= b.pMin.y && p.y < b.pMax.y;
    }
}