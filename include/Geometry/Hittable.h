#pragma once

#include "Global.h"
#include "Math/Vector3.h"
#include "Math/Point3.h"

namespace Just{

    struct HitRecord {
        Point3f position;
        Vector3f normal;
        float hitTime;

        HitRecord() : position(), normal(), hitTime() {}
    };

    struct Hittable{
        virtual bool Intersect() const = 0;
    };
}