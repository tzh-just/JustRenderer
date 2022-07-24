//================================================
// 四元数
//================================================

#pragma once

#include "Global.h"

namespace Just {
    template<typename T>
    struct Quaternion {
        union {
            struct {
                Vector<3, T> image;
                T real;
            };
            struct {
                T x, y, z, w;
            };
            T data[4];
        };

        Quaternion() = default;

        Quaternion(T real_, const Vector<3, T> &image_) : real(real_), image(image_) {}

        Quaternion(T w_, T x_, T y_, T z_) : w(w_), x(x_), y(y_), z(z_) {}

        T &operator[](uint32_t i) {
            assert(i < 4);
            return data[i];
        }

        const T &operator[](uint32_t i) const {
            assert(i < 4);
            return data[i];
        }
    };
}