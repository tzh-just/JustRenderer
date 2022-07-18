//================================================
// 相交
//================================================

#pragma once

#include "Vector.h"

namespace Just {

    struct HitRecord {
        Vector3f position;
        Vector3f normal;

        HitRecord() : position(0), normal(0) {}

        HitRecord(const Vector3f &position_, const Vector3f &normal_)
                : position(position_), normal(normal_) {}
    };

//输出
//----------------------------------------------------------------------------------------------------------
    inline std::ostream &operator<<(std::ostream &os, const HitRecord &record) {
        return os << "position = " << record.position << std::endl
                  << "normal   = " << record.normal;
    }

    struct Hittable {
        virtual HitRecord Intersect(const Ray3f &ray) = 0;
    };
}