#pragma once

#include "Global.h"
#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Shape/Mesh.h"
#include "Geometry/Ray.h"

namespace Just {

struct Sphere : Shape {
    Point3f center;
    float radius;

    Sphere() : center(), radius() {}

    Sphere(const Point3f& position, float radius) : center(position), radius(radius) {}

    //球体与光线求交
    bool Intersect(const Ray& ray, HitRecord* record) const {
        //t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
        Vector3f op = ray.origin - center;
        float h = Dot(op, ray.direction);//h=b/2
        float det = h * h - Dot(op, op) + radius * radius;

        //判断交点时间是否最近
        if (det < 0)
            return false;
        det = sqrt(det);
        record->hitTime = -h - det;
        if (record->hitTime < kEpsilon || record->hitTime > ray.tMax)
            record->hitTime = -h + det;
        if (record->hitTime < kEpsilon || record->hitTime > ray.tMax)
            return false;

        //记录相交信息
        record->point = ray.origin + ray.direction * record->hitTime;
        //record->normal = Normalize(record->point - position);
        return true;
    }
};

}
