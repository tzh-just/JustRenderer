//================================================
// 球体
//================================================

#pragma once

#include <Global.h>
#include <Math/Vector3.h>
#include "HitRecord.h"
#include "Ray3.h"

namespace just
{

    struct Sphere
    {
        Vector3f position;
        float radius;

        constexpr Sphere() : position(), radius() {}

        constexpr Sphere(const Vector3f& pos_, float r) : position(pos_), radius(r) {}

        //球体与光线求交
        constexpr bool Sphere::Intersect(const Ray3f& ray, HitRecord* record) const
        {
            //t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
            Vector3f op = ray.origin - position;
            float h = op.Dot(ray.direction);//h=b/2
            float det = h * h - op.Dot(op) + radius * radius;

            //判断交点时间是否最近
            if (det < 0)
                return false;
            det = sqrt(det);
            record->hitTime = -h - det;
            if (record->hitTime < kEpsilon || record->hitTime > ray.hitTime)
                record->hitTime = -h + det;
            if (record->hitTime < kEpsilon || record->hitTime > ray.hitTime)
                return false;

            //记录相交信息
            record->position = ray.origin + ray.direction * record->hitTime;
            record->normal = (record->position - position).Normalize();
            return true;
        }

        //输出
        friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere)
        {
            return os << sphere.position << ", " << "radius   = " << sphere.radius;
        }
    };

}
