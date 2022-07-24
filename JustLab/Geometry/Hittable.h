//================================================
// 相交
//================================================

#pragma once

#include "../Global.h"
#include "Math/Vector.h"
#include "Ray.h"

namespace Just {

    struct HitRecord {
        Vector3f position;
        Vector3f normal;

        float time;
        bool isHit;

        HitRecord() : position(0), normal(0), time(0), isHit(false) {}
    };

    inline std::ostream &operator<<(std::ostream &os, const HitRecord &record) {
        return os << "position = " << record.position << std::endl
                  << "normal   = " << record.normal;
    }

    class Hittable {
        virtual HitRecord Intersect(Ray3f &ray) = 0;
    };
}