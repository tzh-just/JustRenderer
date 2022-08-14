//================================================
// 三维包围盒
//================================================

#pragma once

#include "Global.h"
#include "Math/Vector3.h"
#include "Ray3.h"

namespace Just
{
    template<typename T>
    struct BoundingBox3
    {
        using BoundingBox = BoundingBox3<T>;
        using Vector = Vector3<T>;

        Vector min, max;

        constexpr BoundingBox3() : min(std::numeric_limits<T>::max()), max(std::numeric_limits<T>::lowest()) {}

        constexpr BoundingBox3(const Vector& v1, const Vector& v2) : min(v1), max(v2) {}

        //包围盒最长维度
        constexpr size_t MajorAxis() const
        {
            size_t major = 0;
            Vector diff = max - min;
            major = diff[1] > diff[major] ? 1 : major;
            major = diff[2] > diff[major] ? 2 : major;
            return major;
        }

        //求包围盒最短的维度
        constexpr size_t MinorAxis() const
        {
            size_t major = 0;
            Vector diff = max - min;
            major = diff[1] < diff[major] ? 1 : major;
            major = diff[2] < diff[major] ? 2 : major;
            return major;
        }

        //包围盒表面积
        constexpr T SurfaceArea() const
        {
            Vector diff = max - min;
            return diff.x * diff.y * diff.z;
        }

        //扩展包围盒
        constexpr void ExpandBy(const BoundingBox& bbox)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                min[i] = std::min(min[i], bbox.min[i]);
                max[i] = std::max(max[i], bbox.max[i]);
            }
        }

        constexpr void ExpandBy(const Vector& point)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                min[i] = std::min(min[i], point[i]);
                max[i] = std::max(max[i], point[i]);
            }
        }

        //取包围盒中心点坐标
        constexpr Vector Centroid() const
        {
            return (max + min) * 0.5f;
        }

        //取包围盒拐角点
        constexpr Vector Corner(size_t cornerIndex)
        {
            Vector corner;
            for (size_t i = 0; i < 3; ++i)
            {
                corner[i] = (cornerIndex & (1 << i)) ? max[i] : min[i];
            }
            return corner;
        }

        //包围盒重叠
        bool Overlaps(const BoundingBox& bbox)
        {
            return min < bbox.max && max > bbox.min;
        }

        //与射线求交
        constexpr bool Intersect(const Ray3f& ray) const
        {

            Vector t0 = (min - ray.origin) / ray.direction;
            Vector t1 = (max - ray.origin) / ray.direction;

            Vector maxTime = MaxVector(t0, t1);
            Vector minTime = MinVector(t0, t1);

            T enterTime = minTime.MaxValue();
            T exitTime = maxTime.MinValue();

            //射线与包围盒不相交或者已经和别的包围盒相交
            if (enterTime > exitTime + kEpsilon ||
                exitTime < 0.0f ||
                enterTime < ray.hitTime)
            {
                return false;
            }

            return true;
        }

        //输出
        friend std::ostream& operator<<(std::ostream& os, const BoundingBox& bbox)
        {
            return os << "{" << "min: " << bbox.min << ", max: " << bbox.max << "}";
        }
    };

    using BoundingBox3f = BoundingBox3<float>;

}