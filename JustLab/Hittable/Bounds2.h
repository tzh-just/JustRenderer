//================================================
// 二维包围盒
//================================================

#pragma once

#include "Global.h"
#include "Math/Vector2.h"

namespace Just
{
    template<typename T>
    struct Bounds2
    {
        using BoundingBox = Bounds2<T>;
        using Vector = Vector2<T>;

        Vector min, max;

        constexpr Bounds2() : min(std::numeric_limits<T>::max()), max(std::numeric_limits<T>::lowest()) {}

        constexpr Bounds2(const Vector& v1, const Vector& v2) : min(v1), max(v2) {}

        //包围盒被覆盖：截断溢出部分
        void CoveredBy(const BoundingBox& bbox)
        {
            min = MaxVector(min, bbox.min);
            max = MinVector(max, bbox.max);
        }

        //输出
        friend std::ostream& operator<<(std::ostream& os, const BoundingBox& bbox)
        {
            return os << "{" << "min: " << bbox.min << ", max: " << bbox.max << "}";
        }
    };

    using BoundingBox2f = Bounds2<float>;

}