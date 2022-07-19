//================================================
// 矩形形模板
//================================================

#pragma once

#include "Just/Global.h"
#include "Math/Vector.h"
#include "Graphics/Transform.h"
#include "Graphics/Vertex.h"
#include "Geometry/Ray.h"
#include "Hittable.h"

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

    //输出
    //----------------------------------------------------------------------------------------------------------
    template<size_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Rectangle<N, T> &rect) {
        return os << "===============================================" << std::endl
                  << "Vertex A" << std::endl
                  << rect[0] << std::endl
                  << "-----------------------------------------------" << std::endl
                  << "Vertex B" << std::endl
                  << rect[1] << std::endl
                  << "-----------------------------------------------" << std::endl
                  << "Vertex C" << std::endl
                  << rect[2] << std::endl
                  << "-----------------------------------------------" << std::endl
                  << "Vertex D" << std::endl
                  << rect[3] << std::endl
                  << "===============================================" << std::endl;
    }
}