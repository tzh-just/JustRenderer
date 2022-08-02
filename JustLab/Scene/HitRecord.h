//================================================
// 射线与几何体相交信息
//================================================

#pragma once

#include <Global.h>
#include <Math/Vector3.h>

namespace just
{

    struct HitRecord
    {
        Vector3f position;
        Vector3f normal;
        float hitTime;

        constexpr HitRecord() : position(), normal(), hitTime() {}

        friend std::ostream& operator<<(std::ostream& os, const HitRecord& record)
        {
            return os << "{position = " << record.position << ", normal   = " << record.normal << "}";
        }
    };

}