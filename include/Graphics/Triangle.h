//================================================
// 三角形模板
//================================================

#pragma once

#include "Math/Vector.h"
#include "Math/Transform.h"
#include "Math/Vertex.h"
#include "Graphics/Object.h"

namespace Just {

    template<size_t N, typename T>
    struct Triangle : Object {
        union {
            Vertex<N, T> vertices[3];
            Vertex<N, T> a, b, c;
        };

        Triangle(const Vertex<N, T> &v1, const Vertex<N, T> &v2, const Vertex<N, T> &v3) : vertices{v1, v2, v3} {}

        Vertex<N, T> &operator[](size_t i) {
            assert(i < 3);
            return vertices[i];
        }

        const Vertex<N, T> &operator[](size_t i) const {
            assert(i < 3);
            return vertices[i];
        }

        HitRecord Intersect(Ray3f &ray) override {
            HitRecord record;
            return record;
        }
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    template<size_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Triangle<N, T> &triangle) {
        return os << "-----------------------------------------------" << std::endl
                  << triangle[0] << std::endl
                  << "-----------------------------------------------" << std::endl
                  << triangle[1] << std::endl
                  << "-----------------------------------------------" << std::endl
                  << triangle[2] << std::endl;
    }

    using Triangle2i = Triangle<2, int>;
    using Triangle3f = Triangle<3, float>;
}