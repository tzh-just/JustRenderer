//================================================
// 三维包围盒
//================================================

#pragma once

#include "Global.h"
#include "Math/Point.h"
#include "Ray.h"

namespace Just
{
    template<size_t N, typename T>
    struct Bounds
    {
        Point<N, T> min, max;

        constexpr Bounds() : min(std::numeric_limits<T>::max()), max(std::numeric_limits<T>::lowest()) {}

        constexpr Bounds(const Point<N, T> &v1, const Point<N, T> &v2) : min(v1), max(v2) {}

        //包围盒被覆盖：截断溢出部分
        constexpr void CoveredBy(const Bounds<N, T> &bbox)
        {
            min = MaxPoint(min, bbox.min);
            max = MinPoint(max, bbox.max);
        }

        //包围盒最长维度
        constexpr size_t MajorAxis() const
        {
            size_t major = 0;
            Point<N, T> diff = max - min;
            major = diff[1] > diff[major] ? 1 : major;
            major = diff[2] > diff[major] ? 2 : major;
            return major;
        }

        //求包围盒最短的维度
        constexpr size_t MinorAxis() const
        {
            size_t major = 0;
            Point<N, T> diff = max - min;
            major = diff[1] < diff[major] ? 1 : major;
            major = diff[2] < diff[major] ? 2 : major;
            return major;
        }

        //包围盒表面积
        constexpr T SurfaceArea() const
        {
            Point<N, T> diff = max - min;
            T sum;
            for (int i = 0; i < N; i++)
            {
                sum *= diff[i];
            }
            return sum;
        }

        //扩展包围盒
        constexpr void ExpandBy(const Bounds<N, T> &bbox)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                min[i] = std::min(min[i], bbox.min[i]);
                max[i] = std::max(max[i], bbox.max[i]);
            }
        }

        constexpr void ExpandBy(const Point<N, T> &point)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                min[i] = std::min(min[i], point[i]);
                max[i] = std::max(max[i], point[i]);
            }
        }

        //取包围盒中心点坐标
        constexpr Point<N, T> Centroid() const
        {
            return (max + min) * 0.5f;
        }

        //取包围盒拐角点
        constexpr Point<N, T> Corner(size_t cornerIndex)
        {
            Point<N, T> corner;
            for (size_t i = 0; i < 3; ++i)
            {
                corner[i] = (cornerIndex & (1 << i)) ? max[i] : min[i];
            }
            return corner;
        }

        //包围盒重叠
        constexpr bool Overlaps(const Bounds<N, T> &bbox)
        {
            return min < bbox.max && max > bbox.min;
        }

        //与射线求交

        constexpr bool Intersect(const Ray<N, T> &ray) const
        {

            Point<N, T> t0 = (min - ray.origin) / ray.direction;
            Point<N, T> t1 = (max - ray.origin) / ray.direction;

            Point<N, T> maxTime = MaxPoint(t0, t1);
            Point<N, T> minTime = MinPoint(t0, t1);

            T enterTime = MaxValue(minTime);
            T exitTime = MinValue(maxTime);

            //射线与包围盒不相交或者已经和别的包围盒相交
            if (enterTime > exitTime + kEpsilon ||
                exitTime < 0.0f ||
                enterTime < ray.hitTime)
            {
                return false;
            }

            return true;
        }
    };

    //输出
    std::ostream &operator<<(std::ostream &os, const Bounds &bbox)
    {
        return os << "{" << "min: " << bbox.min << ", max: " << bbox.max << "}";
    }

    using Bounds2f = Bounds<2, float>;
    using Bounds3f = Bounds<3, float>;

}