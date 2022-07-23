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

        T &operator[](size_t i) {
            assert(i < 4);
            return data[i];
        }

        const T &operator[](size_t i) const {
            assert(i < 4);
            return data[i];
        }
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const Quaternion<T> &q) {
        return os << "{" << "real: " << q.real << ", image: " << q.image << "}";
    }

    //四元数的共轭
    template<typename T>
    inline Quaternion<T> Conjugate(const Quaternion<T> &q) {
        return {q.real, -q.image};
    }

    //四元数的逆
    template<typename T>
    inline Quaternion<T> Invert(const Quaternion<T> &q) {
        return {q.real, -q.image};
    }

    //归一化
    template<typename T>
    inline Quaternion<T> Normalize(const Quaternion<T> &q) {
        return {q.real, -q.image};
    }

    //取模
    template<typename T>
    inline Quaternion<T> Norm(const Quaternion<T> &q) {
        auto norm = Norm(q.image);
        return std::sqrt(q.real * q.real + Dot(q.image, q.image));
    }

    //纯四元数
    template<typename T>
    inline Quaternion<T> Pure(const Quaternion<T> &q) {
        return {0, q.image};
    }

    //旋转
    template<typename T>
    inline Matrix<4, 4, T> Rotate(T angle, const Vector<3, T> &axis) {
        angle /= 2;
        Quaternion < T > q(Cos(angle), Sin(angle) * axis);
        return {
                {1 - 2 * q.y * q.y - 2 * q.z * q.z, 2 * q.x * q.y - 2 * q.w * q.z,     2 * q.x * q.z + 2 * q.w * q.y},
                {2 * q.x * q.y + 2 * q.w * q.z,     1 - 2 * q.x * q.x - 2 * q.z * q.z, 2 * q.y * q.z - 2 * q.w * q.x},
                {2 * q.x * q.z - 2 * q.w * q.y,     2 * q.y * q.z + 2 * q.w * q.x,     1 - 2 * q.x * q.x - 2 * q.y * q.y}
        };
    }

    //加法
    template<typename T>
    inline Quaternion<T> operator+(const Quaternion<T> &q, T value) {
        return {q.real + value, q.image * value};
    }

    template<typename T>
    inline Quaternion<T> operator+(T value, const Quaternion<T> &q) {
        return {q.real + value, q.image * value};
    }

    //乘法
    template<typename T>
    inline Quaternion<T> operator*(const Quaternion<T> &q1, const Quaternion<T> &q2) {
        return {
                q1.real * q2.real - Dot(q1.image, q2.image),
                q1.real * q2.image + q2.real * q1.image + Cross(q1.image, q2.image)
        };
    }

}