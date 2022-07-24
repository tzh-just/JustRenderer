//================================================
// 球体
//================================================

#pragma once

#include "Math/VectorExtension.h"
#include "Hittable.h"
#include "Ray.h"

namespace Just {

    struct Sphere : Hittable {
        Vector3f position;
        float radius;

        explicit Sphere(float r) : position(), radius(r) {}

        Sphere(const Vector3f &pos_, float r) : position(pos_), radius(r) {}

        HitRecord Intersect(Ray3f &ray) override {
            HitRecord record;

            //计算相交
            //t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
            Vector3f op = ray.origin - position;
            //h=b/2
            float h = Dot(op, ray.direction);
            float det = h * h - Dot(op, op) + radius * radius;

            //不相交直接返回
            if (det < 0)
                return record;

            //相交则记录时间
            det = sqrt(det);
            record.time = -h - det;

            //相交但交点都为负或者不是最近的交点都直接返回
            if (record.time < EPS || record.time > ray.time)
                record.time = -h + det;
            if (record.time < EPS || record.time > ray.time)
                return record;

            //记录交点信息
            record.isHit = true;
            record.position = ray.At(record.time);
            record.normal = Normalize(record.position - position);

            return record;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Sphere &sphere) {
        return os << sphere.position << ", " << "radius   = " << sphere.radius;
    }
}
