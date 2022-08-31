#pragma once

#include "Global.h"
#include "Math/Point3.h"
#include "Math/Vector3.h"
#include "Ray.h"

namespace Just {
    template<typename T>
    struct Bounds3 {
        Point3<T> pMin, pMax;

        Bounds3() : pMin(std::numeric_limits<T>::max()),
                    pMax(std::numeric_limits<T>::lowest()) {}

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
            return Point3<T>((*this)[(i & 1)].r, (*this)[(i & 2)].g, (*this)[(i & 4)].b);
        }

        //包围盒最长维度
        int MajorAxis() const {
            Vector3<T> d = Diagonal();
            return (d.x > d.y) ? ((d.x > d.z) ? 0 : 2) : ((d.y > d.z) ? 1 : 2);
        }

        //包围盒中心坐标点
        Point3<T> Centroid() const { return (pMax + pMin) * 0.5f; }

        //包围盒对角线向量
        Vector3<T> Diagonal() const { return pMax - pMin; }

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

        //包围盒与射线相交检测
        bool RayIntersect(const Ray& ray) const;

        //合并包围盒
        static Bounds3<T> Union(const Bounds3<T>& b1, const Bounds3<T>& b2);

        //扩展包围盒
        static Bounds3<T> Expand(const Bounds3<T>& b, const Point3<T>& p);

        //求两包围盒交集
        static Bounds3<T> Intersect(const Bounds3<T>& b1, const Bounds3<T>& b2);

        //检测包围盒是否重叠
        static bool Overlaps(const Bounds3<T>& b1, const Bounds3<T>& b2);

        //检测点在框内：包括边界上的点
        static bool Inside(const Point3<T>& p, const Bounds3<T>& b);

        //检测点在框内：不包括边界上的点
        static bool InsideExclusive(const Point3<T>& p, const Bounds3<T>& b);
    };

    using Bounds3f = Bounds3<float>;
}