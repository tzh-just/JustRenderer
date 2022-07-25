//================================================
// 向量函数扩展
//================================================

#pragma once

#include "Vector.h"

namespace Just {
    //输出
    template<uint32_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Vector<N, T> &v) {
        os << "(";
        for (uint32_t i = 0; i < N; i++) {
            os << v.data[i];
            if (i + 1 != N)
                os << ",";
        }
        os << ")";
        return os;
    }

    //取反
    template<uint32_t N, typename T>
    inline Vector<N, T> operator-(const Vector<N, T> &v) {
        Vector<N, T> tmp;
        for (uint32_t i = 0; i < N; i++)
            tmp[i] = -v[i];
        return tmp;
    }

    //加法
    template<uint32_t N, typename T>
    inline Vector<N, T> operator+(const Vector<N, T> &v1, const Vector<N, T> &v2) {
        Vector<N, T> tmp;
        for (uint32_t i = 0; i < N; i++)
            tmp[i] = v1[i] + v2[i];
        return tmp;
    }

    //减法
    template<uint32_t N, typename T>
    inline Vector<N, T> operator-(const Vector<N, T> &v1, const Vector<N, T> &v2) {
        Vector<N, T> tmp;
        for (uint32_t i = 0; i < N; i++)
            tmp[i] = v1[i] - v2[i];
        return tmp;
    }

    //乘法
    template<uint32_t N, typename T>
    inline Vector<N, T> operator*(const Vector<N, T> &v1, const Vector<N, T> &v2) {
        Vector<N, T> tmp;
        for (uint32_t i = 0; i < N; i++)
            tmp[i] = v1[i] * v2[i];
        return tmp;
    }

    //赋值加
    template<uint32_t N, typename T>
    inline Vector<N, T> &operator+=(Vector<N, T> &v1, const Vector<N, T> &v2) {
        for (uint32_t i = 0; i < N; i++)
            v1[i] += v2[i];
        return v1;
    }

    //赋值减
    template<uint32_t N, typename T>
    inline Vector<N, T> &operator-=(Vector<N, T> &v1, const Vector<N, T> &v2) {
        for (uint32_t i = 0; i < N; i++) {
            v1[i] -= v2[i];
        }
        return v1;
    }

    //赋值乘
    template<uint32_t N, typename T>
    inline Vector<N, T> &operator*=(Vector<N, T> &v1, const Vector<N, T> &v2) {
        for (uint32_t i = 0; i < N; i++)
            v1[i] *= v2[i];
        return v1;
    }

    //数乘
    template<uint32_t N, typename T, typename U>
    inline Vector<N, T> operator*(const Vector<N, T> &v1, U k) {
        Vector<N, T> tmp;
        for (uint32_t i = 0; i < N; i++)
            tmp[i] = v1[i] * static_cast<T>(k);
        return tmp;
    }

    template<uint32_t N, typename T, typename U>
    inline Vector<N, T> operator*(U k, const Vector<N, T> &v1) {
        Vector<N, T> tmp;
        for (uint32_t i = 0; i < N; i++)
            tmp[i] = v1[i] * static_cast<T>(k);
        return tmp;
    }

    template<uint32_t N, typename T, typename U>
    inline Vector<N, T> operator/(const Vector<N, T> &v1, U k) {
        Vector<N, T> tmp;
        for (uint32_t i = 0; i < N; i++)
            tmp[i] = v1[i] / static_cast<T>(k);
        return tmp;
    }

    //赋值数乘
    template<uint32_t N, typename T, typename U>
    inline Vector<N, T> &operator*=(Vector<N, T> &v, U k) {
        for (uint32_t i = 0; i < N; i++)
            v[i] *= static_cast<T>(k);
        return v;
    }

    template<uint32_t N, typename T, typename U>
    inline Vector<N, T> &operator/=(Vector<N, T> &v, U k) {
        for (uint32_t i = 0; i < N; i++)
            v[i] /= static_cast<T>(k);
        return v;
    }

    //比较
    template<uint32_t N, typename T>
    inline bool operator<(Vector<N, T> &v1, const Vector<N, T> &v2) {
        for (uint32_t i = 0; i < N; i++)
            if (v1[i] >= v2[i])
                return false;
        return true;
    }

    template<uint32_t N, typename T>
    inline bool operator>(Vector<N, T> &v1, const Vector<N, T> &v2) {
        for (uint32_t i = 0; i < N; i++)
            if (v1[i] <= v2[i])
                return false;
        return true;
    }

    template<uint32_t N, typename T>
    inline bool operator<=(Vector<N, T> &v1, const Vector<N, T> &v2) {
        for (uint32_t i = 0; i < N; i++)
            if (v1[i] > v2[i])
                return false;
        return true;
    }

    template<uint32_t N, typename T>
    inline bool operator>=(Vector<N, T> &v1, const Vector<N, T> &v2) {
        for (uint32_t i = 0; i < N; i++)
            if (v1[i] < v2[i])
                return false;
        return true;
    }

    //长度
    template<uint32_t N, typename T>
    inline T Length(const Vector<N, T> &v) {
        T sum = 0;
        for (uint32_t i = 0; i < N; i++)
            sum += v[i] * v[i];
        return std::sqrt(sum);
    }

    //点积
    template<uint32_t N, typename T>
    inline T Dot(const Vector<N, T> &v1, const Vector<N, T> &v2) {
        T sum = 0;
        for (uint32_t i = 0; i < N; i++)
            sum += v1[i] * v2[i];
        return sum;
    }

    //特化二维矢量叉积
    template<typename T>
    inline T Cross(const Vector<2, T> &v1, const Vector<2, T> &v2) {
        return v1.x * v2.y - v2.x * v1.y;
    }

    //特化三维矢量叉积
    template<typename T>
    inline Vector<3, T> Cross(const Vector<3, T> &v1, const Vector<3, T> &v2) {
        return {v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v2.z * v1.x, v1.x * v2.y - v2.x * v1.y};
    }

    //归一化
    template<uint32_t N, typename T>
    inline Vector<N, T> Normalize(const Vector<N, T> &v) {
        T sum = 0;
        for (uint32_t i = 0; i < N; i++)
            sum += v[i] * v[i];
        return v / std::sqrt(sum);
    }

    //各维度最小值
    template<uint32_t N, typename T>
    inline Vector<N, T> MinValue(const Vector<N, T> &v1, const Vector<N, T> &v2) {
        Vector<N, T> min;
        for (uint32_t i = 0; i < N; i++)
            min[i] = std::min(v1[i], v2[i]);
        return min;
    }

    //各维度最大值
    template<uint32_t N, typename T>
    inline Vector<N, T> MaxValue(const Vector<N, T> &v1, const Vector<N, T> &v2) {
        Vector<N, T> max;
        for (uint32_t i = 0; i < N; i++)
            max[i] = std::max(v1[i], v2[i]);
        return max;
    }

    //插值
    template<uint32_t N, typename T, typename U>
    inline Vector<N, T> Lerp(const Vector<N, T> &v1, const Vector<N, T> &v2, U alpha) {
        return v1 * (1 - alpha) + v2;
    }
}