//================================================
// 二维包围盒
//================================================

#pragma once

#include <Global.h>
#include <Math/Vector2.h>

namespace just
{
    template<typename T>
    struct BoundingBox2
    {
        using BoundingBox = BoundingBox2<T>;
        using Vector = Vector2<T>;

        Vector min, max;

        constexpr BoundingBox2() : min(std::numeric_limits<T>::max()), max(std::numeric_limits<T>::lowest()) {}

        constexpr BoundingBox2(const Vector& v1, const Vector& v2) : min(v1), max(v2) {}

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

    using BoundingBox2f = BoundingBox2<float>;

}