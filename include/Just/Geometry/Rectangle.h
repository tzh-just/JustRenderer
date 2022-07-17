#pragma once

#include "Just/Math/Vector.h"
#include "Just/Graphic/Transform.h"
#include "Vertex.h"
#include "Ray.h"

namespace Just {
    template<size_t N, typename T>
    struct Rectangle : Hittable {
        union {
            Vertex<N, T> vertices[4];
            Vertex<N, T> a, b, c, d;
        };

        Rectangle(const Vertex<N, T> &v1, const Vertex<N, T> &v2, const Vertex<N, T> &v3, const Vertex<N, T> &v4) : vertices{v1, v2, v3, v4} {}

        Vertex<N, T> &operator[](size_t i) {
            assert(i < 4);
            return vertices[i];
        }

        const Vertex<N, T> &operator[](size_t i) const {
            assert(i < 4);
            return vertices[i];
        }

        HitRecord Intersect(const Ray3f &ray) override {
            HitRecord record;
            return record;
        }
    };
}