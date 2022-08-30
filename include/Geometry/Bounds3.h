#pragma once

#include "Global.h"
#include "Math/Point3.h"
#include "Math/Vector3.h"
#include "Ray.h"

namespace Just {
    template<typename T>
    struct Bounds3 {
        Point3<T> pMin, pMax;

        Bounds3() : pMin(std::numeric_limits<T>::max()),pMax(std::numeric_limits<T>::lowest()){}

        explicit Bounds3(const Point3<T>& p) : pMin(p), pMax(p) {}

        Bounds3(const Point3f& p1, const Point3f& p2)
                : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)),
                  pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z)) {}

        const Point3<T>& operator[](int i) const {
            assert(i >= 0 && i <= 2);
            return (&pMin)[i];
        }

        Point3<T>& operator[](int i) {
            assert(i >= 0 && i <= 2);
            return (&pMin)[i];
        }

        //包围盒拐角点
        Point3<T> Corner(int i) const {
            return Point3<T>(
                    (*this)[(i & 1)].r,
                    (*this)[(i & 2)].g,
                    (*this)[(i & 4)].b
            );
        }

        //包围盒最长维度
        int MajorAxis() const {
            Vector3<T> d = Diagonal();
            return (d.x > d.y) ? ((d.x > d.z) ? 0 : 2) : ((d.y > d.z) ? 1 : 2);
        }

        //包围盒中心坐标点
        Point3<T> Centroid() const {
            return (pMax + pMin) * 0.5f;
        }

        //包围盒对角线向量
        Vector3<T> Diagonal() const {
            return pMax - pMin;
        }

        //包围盒表面积
        T SurfaceArea() const {
            Vector3<T> d = Diagonal();
            return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
        }

        //包围盒体积
        T Volume() const {
            Vector3<T> d = Diagonal();
            return d.x * d.y * d.z;
        }

        //与射线求交

        bool Intersect(const Ray& ray) const {
            Vector3f t0 = (pMin - ray.origin) / ray.direction;
            Vector3f t1 = (pMax - ray.origin) / ray.direction;

            Vector3f maxTime = Max(t0, t1);
            Vector3f minTime = Min(t0, t1);

            float enterTime = MaxComponent(minTime);
            float exitTime = MinComponent(maxTime);

            //射线与包围盒不相交或者已经和别的包围盒相交
            if (enterTime > exitTime + kEpsilon ||
                exitTime < 0.0f ||
                enterTime < ray.tMax) {
                return false;
            }

            return true;
        }
    };

    //合并包围盒
    template<typename T>
    Bounds3<T> Union(const Bounds3<T>& b1, const Bounds3<T>& b2) {
        return Bounds3<T>(Min(b1.pMin, b2.pMin), Max(b1.pMax, b2.pMax));
    }

    //扩展包围盒
    template<typename T>
    Bounds3<T> Expand(const Bounds3<T>& b, const Point3<T>& p) {
        return Bounds3<T>(Min(b.pMin, p), Max(b.pMax, p));
    }

    //求两包围盒交集
    template<typename T>
    Bounds3<T> Intersect(const Bounds3<T>& b1, const Bounds3<T>& b2) {
        return Bounds3<T>(Max(b1.pMin, b2.pMin), Min(b1.pMax, b2.pMax));
    }

    //检测包围盒是否重叠
    template<typename T>
    bool Overlaps(const Bounds3<T>& b1, const Bounds3<T>& b2) {
        bool x = (b1.pMax.x >= b2.pMin.x) && (b1.pMin.x <= b2.pMax.x);
        bool y = (b1.pMax.y >= b2.pMin.y) && (b1.pMin.y <= b2.pMax.y);
        bool z = (b1.pMax.z >= b2.pMin.z) && (b1.pMin.z <= b2.pMax.z);
        return x && y && z;
    }

    //检测点则框内：包括边界上的点
    template<typename T>
    bool Inside(const Point3<T>& p, const Bounds3<T>& b) {
        return p.x >= b.pMin.x && p.x <= b.pMax.x &&
               p.y >= b.pMin.y && p.y <= b.pMax.y &&
               p.z >= b.pMin.z && p.z <= b.pMax.z;
    }

    //检测点则框内：不包括边界上的点
    template<typename T>
    bool InsideExclusive(const Point3<T>& p, const Bounds3<T>& b) {
        return p.x >= b.pMin.x && p.x < b.pMax.x &&
               p.y >= b.pMin.y && p.y < b.pMax.y &&
               p.z >= b.pMin.z && p.z < b.pMax.z;
    }

    using Bounds3f = Bounds3<float>;
}