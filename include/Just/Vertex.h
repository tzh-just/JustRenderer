//================================================
// 顶点模板
//================================================

#pragma once

#include "Vector.h"
#include "Transform.h"

namespace Just {

    template<size_t N, typename T>
    struct Vertex {
        Vector<N, T> position;
        Vector<3, T> normal;
        Vector<2, T> uv;

        Vertex() : position(0), normal(0), uv(0) {}

        explicit Vertex(const Vector<N, T> &pos_) : position(pos_), normal(), uv() {}

        Vertex(const Vector<N, T> &pos_, const Vector<2, T> &normal_, const Vector<3, T> &uv_)
                : position(pos_), normal(normal_), uv(uv_) {}
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    template<size_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Vertex<N, T> &vertex) {
        return os << "position = " << vertex.position << std::endl
                  << "normal   = " << vertex.normal << std::endl
                  << "uv       = " << vertex.uv;
    }

    using Vertex2i = Vertex<2, int>;
    using Vertex3f = Vertex<3, float>;
}