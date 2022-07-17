#pragma once

#include "Just/Math/Vector.h"

namespace Just {
    template<size_t N, typename T>
    struct Ray {
        Vector<N, T> origin;
        Vector<N, T> direction;

        Ray() : origin(0), direction(0) {}

        Ray(const Vector<N, T> &orig, const Vector<N, T> &dir) : origin(orig), direction(dir) {}

        Vector<N, T> At(T time) const {
            return origin + direction * time;
        }
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    template<size_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Ray<N, T> &ray) {
        return os << "-----------------------------------------------" << std::endl
                  << "origin    = " << ray.origin << std::endl
                  << "direction = " << ray.direction << std::endl;
    }

    using Ray3f = Ray<3, float>;

    struct HitRecord {
        Vector3f position;
        Vector3f normal;

        HitRecord() : position(0), normal(0) {}

        HitRecord(const Vector3f &position_, const Vector3f &normal_)
                : position(position_), normal(normal_) {}
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    template<size_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const HitRecord &record) {
        return os << "-----------------------------------------------" << std::endl
                  << "position = " << record.position << std::endl
                  << "normal   = " << record.normal << std::endl;
    }

    struct Hittable {
        virtual HitRecord Intersect(const Ray3f &ray) = 0;
    };
}
