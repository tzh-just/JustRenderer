#pragma once

#include "Just/Math/Vector.h"
#include "Just/Graphic/Transform.h"
#include "Ray.h"

namespace Just {

    struct Sphere : Hittable {
        Transform transform;
        float radius;

        explicit Sphere(float r) : transform(), radius(r) {}
        Sphere(const Transform &trans, float r) : transform(trans), radius(r) {}

        HitRecord Intersect(const Ray3f &ray) override {
            HitRecord record;
            return record;
        }
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    inline std::ostream &operator<<(std::ostream &os, const Sphere &sphere) {
        return os << sphere.transform << std::endl
                  << "radius   = " << sphere.radius << std::endl;
    }
}
