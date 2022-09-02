#pragma once

#include "Global.h"
#include "Math/Vector.h"
#include "Ray.h"

namespace Just {

    struct Bounds3f {
        Point3f pMin, pMax;

        Bounds3f() : pMin(std::numeric_limits<float>::max()),
                     pMax(std::numeric_limits<float>::lowest()) {}

        explicit Bounds3f(const Point3f& p) : pMin(p), pMax(p) {}

        Bounds3f(const Point3f& p1, const Point3f& p2)
                : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)),
                  pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z)) {}

        const Point3f& operator[](size_t i) const {
            assert(i < 2);
            return (&pMin)[i];
        }

        Point3f& operator[](size_t i) {
            assert(i < 2);
            return (&pMin)[i];
        }

        //与射线求交
        bool RayIntersect(const Ray3f& ray) const {
            //t = (P' - O) dot N / D dot N
            //t[tx,ty,tz] = (P' - O) / D
            Vector3f t0 = (pMin - ray.origin) / ray.direction;
            Vector3f t1 = (pMax - ray.origin) / ray.direction;

            Vector3f maxTime = Max(t0, t1);
            Vector3f minTime = Min(t0, t1);

            float enterTime = MaxComponent(minTime);
            float exitTime = MinComponent(maxTime);

            //离开时间为正 && 大于进入时间 && 进入时间小于射线第一次击中时间
            return exitTime > 0.0f && exitTime + kEpsilon > enterTime && enterTime < ray.tMax;
        }

        //包围盒拐角点
        Point3f Corner(int i) const {
            return {
                    (*this)[(i & 1)].r,
                    (*this)[(i & 2)].g,
                    (*this)[(i & 4)].b
            };
        }

        //包围盒中心坐标点
        Point3f Centroid() const { return (pMax + pMin) * 0.5f; }

        //包围盒对角线向量
        Point3f Diagonal() const { return pMax - pMin; }

        //包围盒最长维度
        int MajorAxis() const {
            Point3f d = Diagonal();
            return (d.x > d.y) ? ((d.x > d.z) ? 0 : 2) : ((d.y > d.z) ? 1 : 2);
        }

        //包围盒表面积
        float SurfaceArea() const {
            Point3f d = Diagonal();
            return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
        }

        //包围盒体积
        float Volume() const {
            Point3f d = Diagonal();
            return d.x * d.y * d.z;
        }

        bool Inside(const Vector3f& p) const {
            return p.x >= pMin.x && p.x <= pMax.x &&
                   p.y >= pMin.y && p.y <= pMax.y &&
                   p.z >= pMin.z && p.z <= pMax.z;
        }

        bool InsideExclusive(const Vector3f& p) const {
            return p.x >= pMin.x && p.x < pMax.x &&
                   p.y >= pMin.y && p.y < pMax.y &&
                   p.z >= pMin.z && p.z < pMax.z;
        }

        //扩展包围盒
        void Expand(const Point3f& p) {
            pMin = Min(pMin, p);
            pMax = Max(pMax, p);
        }

        //合并包围盒
        static Bounds3f Union(const Bounds3f& b1, const Bounds3f& b2) {
            return {
                    Min(b1.pMin, b2.pMin),
                    Max(b1.pMax, b2.pMax)
            };
        }

        //包围盒相交部分
        static Bounds3f Intersect(const Bounds3f& b1, const Bounds3f& b2) {
            return {
                    Max(b1.pMin, b2.pMin),
                    Min(b1.pMax, b2.pMax)
            };
        }

        //包围盒覆盖测试
        static bool Overlaps(const Bounds3f& b1, const Bounds3f& b2) {
            bool x = (b1.pMax.x >= b2.pMin.x) && (b1.pMin.x <= b2.pMax.x);
            bool y = (b1.pMax.y >= b2.pMin.y) && (b1.pMin.y <= b2.pMax.y);
            bool z = (b1.pMax.z >= b2.pMin.z) && (b1.pMin.z <= b2.pMax.z);
            return x && y && z;
        }
    };

    struct Bounds2i {
        Point2i pMin, pMax;

        Bounds2i() : pMin(std::numeric_limits<int>::max()), pMax(std::numeric_limits<int>::lowest()) {}

        explicit Bounds2i(const Point2i& p) : pMin(p), pMax(p) {}

        Bounds2i(const Point2i& p1, const Point2i& p2)
                : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
                  pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y)) {}

        bool Inside(const Point2i& p) const {
            return p.x >= pMin.x && p.x <= pMax.x &&
                   p.y >= pMin.y && p.y <= pMax.y;
        }

        bool InsideExclusive(const Point2i& p) const {
            return p.x >= pMin.x && p.x < pMax.x &&
                   p.y >= pMin.y && p.y < pMax.y;
        }
    };
}