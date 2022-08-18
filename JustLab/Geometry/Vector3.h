#pragma once

#include "Global.h"

namespace Just {
    template<typename T>
    struct Vector3 {
        T x, y, z;

        Vector3() { x = y = z = 0; }

        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

        T& operator[](int i) {
            assert(i <= 2 && i >= 0);
            return (&x)[i];
        }

        T operator[](int i) const {
            assert(i <= 2 && i >= 0);
            return (&x)[i];
        }

        float LengthSquared() const {
            return x * x + y * y + z * z;
        }

        float Length() const {
            return std::sqrt(LengthSquared());
        }
    };

    //加法
    template<typename T>
    inline Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2) {
        return Vector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    //赋值加
    template<typename T>
    inline Vector3<T>& operator+=(Vector3<T>& v1, const Vector3<T>& v2) {
        v1.x += v2.x;
        v1.y += v2.y;
        v1.z += v2.z;
        return v1;
    }

    //减法
    template<typename T>
    inline Vector3<T> operator-(Vector3<T>& v1, const Vector3<T>& v2) {
        return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    //赋值减
    template<typename T>
    inline Vector3<T>& operator-=(Vector3<T>& v1, const Vector3<T>& v2) {
        v1.x -= v2.x;
        v1.y -= v2.y;
        v1.z -= v2.z;
        return v1;
    }

    //乘法
    template<typename T>
    inline Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2) {
        return Vector3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

    //赋值乘
    template<typename T>
    inline Vector3<T> operator*=(Vector3<T>& v1, const Vector3<T>& v2) {
        v1.x *= v2.x;
        v1.y *= v2.y;
        v1.z *= v2.z;
        return v1;
    }

    //后数乘
    template<typename T>
    inline Vector3<T> operator*(Vector3<T>& v, T k) {
        return Vector3<T>(v.x * k, v.y * k, v.z * k);
    }

    //前数乘
    template<typename T>
    inline Vector3<T> operator*(T k, const Vector3<T>& v) {
        return v * k;
    }

    //赋值数乘
    template<typename T>
    inline Vector3<T>& operator*=(Vector3<T>& v, T k) {
        assert(!std::isnan(k));
        v.x *= k;
        v.y *= k;
        v.z *= k;
        return v;
    }

    //除法
    template<typename T>
    inline Vector3<T> operator/(const Vector3<T>& v1, const Vector3<T>& v2) {
        return Vector3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
    }

    //赋值除
    template<typename T>
    inline Vector3<T> operator/=(Vector3<T>& v1, const Vector3<T>& v2) {
        v1.x /= v2.x;
        v1.y /= v2.y;
        v1.z /= v2.z;
        return v1;
    }

    //数除
    template<typename T>
    inline Vector3<T> operator/(Vector3<T>& v, T k) {
        assert(k != 0);
        float inv = (float) 1 / k;
        return Vector3<T>(v.x * inv, v.y * inv, v.z * inv);
    }

    //赋值数除
    template<typename T>
    inline Vector3<T>& operator/=(Vector3<T>& v, T k) {
        assert(k != 0);
        float inv = (float) 1 / k;
        v.x *= inv;
        v.y *= inv;
        v.z *= inv;
        return v;
    }

    //取反
    template<typename T>
    inline Vector3<T> operator-(Vector3<T>& v) {
        return Vector3<T>(-v.x, -v.y, -v.z);
    }

    //点乘向量
    template<typename T>
    inline T Dot(const Vector3<T>& v1, const Vector3<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    //向量绝对值
    template<typename T>
    inline T Abs(const Vector3<T>& v) {
        return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
    }

    //向量点乘的绝对值
    template<typename T>
    inline T AbsDot(const Vector3<T>& v1, const Vector3<T>& v2) {
        return Abs(Dot(v1, v2));
    }

    //向量叉乘
    template<typename T>
    inline Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2) {
        return Vector3<T>(
                v1.y * v2.z - v2.y * v1.z,
                v1.z * v2.x - v2.z * v1.x,
                v1.x * v2.y - v2.x * v1.y
        );
    }

    //向量归一化
    template<typename T>
    inline Vector3<T> Normalize(const Vector3<T>& v) {
        return v / v.Length();
    }

    //向量最小坐标值
    template<typename T>
    inline T MinComponent(const Vector3<T>& v) {
        return std::min(std::min(v.x, v.y), v.z);
    }

    //向量最大坐标值
    template<typename T>
    inline T MaxComponent(const Vector3<T>& v) {
        return std::max(std::max(v.x, v.y), v.z);
    }

    //向量最小分量索引
    template<typename T>
    inline int MinDimension(const Vector3<T>& v1, const Vector3<T>& v2) {
        return (v1.x > v2.y) ? ((v1.x > v2.z) ? 0 : 2) : ((v1.y > v2.z) ? 1 : 2);
    }

    //向量最大分量索引
    template<typename T>
    inline int MaxDimension(const Vector3<T>& v1, const Vector3<T>& v2) {
        return (v1.x < v2.y) ? ((v1.x < v2.z) ? 0 : 2) : ((v1.y < v2.z) ? 1 : 2);
    }

    //各维度最小值
    template<typename T>
    inline Vector3<T> Min(const Vector3<T>& v1, const Vector3<T>& v2) {
        return Vector3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z));
    }

    //各维度最大值
    template<typename T>
    inline Vector3<T> Max(const Vector3<T>& v1, const Vector3<T>& v2) {
        return Vector3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z));
    }

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& v1) {
        return os << "<" << v1.x << "," << v1.y << "," << v1.z << ">";
    }

    using Vector3f = Vector3<float>;
}