//================================================
// 相交
//================================================

#pragma once

#include "Vector.h"

namespace Just {

    struct HitRecord {
        Vector3f position;
        Vector3f normal;

        float time;
        bool isHit;

        HitRecord() : position(0), normal(0), time(0), isHit(false) {}
    };

//输出
//----------------------------------------------------------------------------------------------------------
    inline std::ostream &operator<<(std::ostream &os, const HitRecord &record) {
        return os << "position = " << record.position << std::endl
                  << "normal   = " << record.normal;
    }

    struct Hittable {
        virtual HitRecord Intersect(Ray3f &ray) = 0;
    };
}