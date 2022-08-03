//================================================
// 三维矢量
//================================================

#pragma once

#include <Global.h>

namespace Just
{

    template<typename T>
    struct Vector3
    {
        using Vector = Vector3<T>;

        union
        {
            struct
            {
                T x, y, z;
            };
            T data[3];
        };

        constexpr Vector3() : x(0), y(0), z(0) {}

        constexpr explicit Vector3(T val) : x(val), y(val), z(val) {}

        constexpr Vector3(T v1, T v2, T v3) : x(v1), y(v2), z(v3) {}

        constexpr Vector3(const std::initializer_list<T>& list)
        {
            auto it = list.begin();
            for (size_t i = 0; i < 3; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T& operator[](size_t i)
        {
            assert(i < 3);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < 3);
            return data[i];
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector& v)
        {
            return os << "(" << v.x << "," << v.y << "," << v.z << ")";
        }

        //正反
        constexpr Vector operator+() const { return *this; }

        constexpr Vector operator-() const { return {-x, -y, -z}; }

        //四则运算
        constexpr Vector operator+(const Vector& v) const { return {x + v.x, y + v.y, z + v.z}; }

        constexpr Vector operator-(const Vector& v) const { return {x - v.x, y - v.y, z - v.z}; }

        constexpr Vector operator*(const Vector& v) const { return {x * v.x, y * v.y, z * v.z}; }

        constexpr Vector operator/(const Vector& v) const { return {x / v.x, y / v.y, z / v.z}; }

        constexpr void operator+=(const Vector& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
        }

        constexpr void operator-=(const Vector& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        constexpr void operator*=(const Vector& v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
        }

        constexpr void operator/=(const Vector& v)
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;
        }

        //数乘

        constexpr Vector operator*(T k) const { return {x * k, y * k, z * k}; }

        constexpr friend Vector operator*(T k, const Vector& v) { return {v.x * k, v.y * k, v.z * k}; }

        constexpr Vector operator/(T k) const { return {x / k, y / k, z / k}; }

        constexpr void operator*=(T k)
        {
            x *= k;
            y *= k;
            z *= k;
        }

        constexpr void operator/=(T k)
        {
            x /= k;
            y /= k;
            z /= k;
        }

        //比较
        constexpr bool operator>(const Vector& v) const { return x > v.x && y > v.y && z > v.z; }

        constexpr bool operator>=(const Vector& v) const { return x >= v.x && y >= v.y && z >= v.z; }

        constexpr bool operator<(const Vector& v) const { return x < v.x && y < v.y && z < v.z; }

        constexpr bool operator<=(const Vector& v) const { return x <= v.x && y <= v.y && z <= v.z; }

        constexpr T Length() const { return std::sqrt(x * x + y * y + z * z); }

        constexpr T Dot(const Vector& v) const { return x * v.x + y * v.y + z * v.z; }

        constexpr Vector Cross(const Vector& v) { return {y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y}; }

        constexpr Vector Normalize() const { return (*this) / Length(); }

        constexpr T MaxValue() const { return std::max(std::max(x, y), z); }

        constexpr T MinValue() const { return std::min(std::min(x, y), z); }
    };

    //各维度最小值
    template<typename T>
    constexpr Vector3<T> MinVector(const Vector3<T>& v1, const Vector3<T>& v2)
    {
        Vector3<T> min;
        for (size_t i = 0; i < 3; ++i)
        {
            min[i] = std::min(v1[i], v2[i]);
        }
        return min;
    }

    //各维度最大值
    template<typename T>
    constexpr Vector3<T> MaxVector(const Vector3<T>& v1, const Vector3<T>& v2)
    {
        Vector3<T> max;
        for (size_t i = 0; i < 3; ++i)
        {
            max[i] = std::max(v1[i], v2[i]);
        }
        return max;
    }

    using Vector3i = Vector3<int>;
    using Vector3f = Vector3<float>;

}



