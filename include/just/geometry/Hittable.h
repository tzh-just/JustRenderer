//================================================
// 相交
//================================================

#pragma once

#include "Global.h"
#include "Math/VectorExt.h"
#include "Ray.h"

namespace Just {

    struct HitRecord {
        Vector3f position;
        Vector3f normal;

        float time;
        bool isHit;

        HitRecord() : position(), normal(), time(), isHit(false) {}
    };

    inline std::ostream &operator<<(std::ostream &os, const HitRecord &record) {
        return os << "{position = " << record.position << ", normal   = " << record.normal << "}";
    }

    class Hittable {
        virtual HitRecord Intersect(Ray3f &ray) = 0;
    };
}