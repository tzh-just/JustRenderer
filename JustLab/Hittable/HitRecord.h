#pragma once

#include "Global.h"
#include "Geometry/Vector3.h"
#include "Geometry/Point3.h"

namespace Just {

    struct HitRecord {
        Point3f position;
        Vector3f normal;
        float hitTime;

        constexpr HitRecord() : position(), normal(), hitTime() {}
    };

}