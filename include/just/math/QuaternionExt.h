//================================================
// 四元数函数扩展
//================================================

#pragma once

#include "Quaternion.h"
#include "Matrix.h"

namespace Just {
    //输出
    template<typename T>
    inline std::ostream &operator<<(std::ostream &os, const Quaternion<T> &q) {
        return os << "{" << "real: " << q.real << ", image: " << q.image << "}";
    }

    //共轭
    template<typename T>
    inline Quaternion<T> Conjugate(const Quaternion<T> &q) {
        return {q.real, -q.image};
    }

    //逆
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
        Quaternion<T> q(std::cos(Radians(angle)), std::sin(Radians(angle)) * axis);
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