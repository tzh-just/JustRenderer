//================================================
// 边界模板
//================================================

#pragma once

#include "Math/Vector.h"
#include "Hittable.h"
#include "Ray.h"

namespace Just {
    template<size_t N, typename T>
    struct Bounds : Hittable {
        Vector<N, T> min;
        Vector<N, T> max;

        Bounds() : min(), max() {}

        Bounds(const Vector<N, T> &min_, const Vector<N, T> &max_) : min(min_), max(max_) {}

        HitRecord Intersect(Ray3f &ray) override {
            HitRecord record;
            return record;
        }
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    template<size_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Bounds<N, T> &bbox) {
        return os << "{" << "min: " << bbox.min << ", max: " << bbox.max << "}";
    }

    //取包围盒中心点坐标
    template<size_t N, typename T>
    inline Vector<N, T> Centroid(const Bounds<N, T> &bbox) {
        return (bbox.max + bbox.min) * 0.5f;
    }

    //取包围盒拐角点
    template<size_t N, typename T>
    inline Vector<N, T> Corner(const Bounds<N, T> &bbox, uint32_t index) {
        Vector<N, T> corner;
        for (int i = 0; i < N; i++)
            corner[i] = (index & (1 << i)) ? bbox.max[i] : bbox.min[i];
    }

    //合并包围盒
    template<size_t N, typename T>
    inline Vector<N, T> Merge(const Bounds<N, T> &bbox1, const Bounds<N, T> &bbox2) {
        return {MinValue(bbox1.min, bbox1.min), MaxValue(bbox1.max, bbox1.max)};
    }

    //检测包围盒重叠
    template<size_t N, typename T>
    inline bool Overlaps(const Bounds<N, T> &bbox1, const Bounds<N, T> &bbox2) {
        return bbox1.min < bbox1.max && bbox1.max > bbox2.min;
    }

    using Bounds3f = Bounds<3, float>;

}