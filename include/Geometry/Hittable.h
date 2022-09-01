#pragma once

#include "Global.h"
#include "Math/Vector.h"
#include "Math/Vector.h"

namespace Just{

    struct HitRecord {
        Point3f point;
        float hitTime;

        HitRecord() : point(), hitTime() {}
    };

    struct Hittable{
        virtual bool Intersect() const = 0;
    };
}