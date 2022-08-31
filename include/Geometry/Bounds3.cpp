#include "Bounds3.h"

namespace Just {
    //与射线求交
    template<typename T>
    bool Bounds3<T>::RayIntersect(const Ray& ray) const {
        //t = (P' - O) dot N / D dot N
        //[tx,ty,tz] = (P' - O) / D
        Vector3f t0 = (pMin - ray.origin) / ray.direction;
        Vector3f t1 = (pMax - ray.origin) / ray.direction;

        Vector3f maxTime = Max(t0, t1);
        Vector3f minTime = Min(t0, t1);

        float enterTime = MaxComponent(minTime);
        float exitTime = MinComponent(maxTime);

        //离开时间为正 && 大于进入时间 && 进入时间小于射线第一次击中时间
        return exitTime > 0.0f && exitTime > enterTime - kEpsilon && enterTime < ray.tMax;
    }

    template<typename T>
    Bounds3<T> Bounds3<T>::Union(const Bounds3<T>& b1, const Bounds3<T>& b2) {
        return Bounds3<T>(Min(b1.pMin, b2.pMin), Max(b1.pMax, b2.pMax));
    }

    template<typename T>
    Bounds3<T> Bounds3<T>::Expand(const Bounds3<T>& b, const Point3<T>& p) {
        return Bounds3<T>(Min(b.pMin, p), Max(b.pMax, p));
    }

    template<typename T>
    Bounds3<T> Bounds3<T>::Intersect(const Bounds3<T>& b1, const Bounds3<T>& b2) {
        return Bounds3<T>(Max(b1.pMin, b2.pMin), Min(b1.pMax, b2.pMax));
    }

    template<typename T>
    bool Bounds3<T>::Overlaps(const Bounds3<T>& b1, const Bounds3<T>& b2) {
        bool x = (b1.pMax.x >= b2.pMin.x) && (b1.pMin.x <= b2.pMax.x);
        bool y = (b1.pMax.y >= b2.pMin.y) && (b1.pMin.y <= b2.pMax.y);
        bool z = (b1.pMax.z >= b2.pMin.z) && (b1.pMin.z <= b2.pMax.z);
        return x && y && z;
    }

    template<typename T>
    bool Bounds3<T>::Inside(const Point3<T>& p, const Bounds3<T>& b) {
        return p.x >= b.pMin.x && p.x <= b.pMax.x &&
               p.y >= b.pMin.y && p.y <= b.pMax.y &&
               p.z >= b.pMin.z && p.z <= b.pMax.z;
    }

    template<typename T>
    bool Bounds3<T>::InsideExclusive(const Point3<T>& p, const Bounds3<T>& b) {
        return p.x >= b.pMin.x && p.x < b.pMax.x &&
               p.y >= b.pMin.y && p.y < b.pMax.y &&
               p.z >= b.pMin.z && p.z < b.pMax.z;
    }
}