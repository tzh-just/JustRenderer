#pragma once

#include "Global.h"

namespace Just
{
    template<size_t N, typename T>
    struct Vector
    {
        T data[N];

        constexpr Vector() { for (size_t i = 0; i < N; i++) data[i] = T(); }

        constexpr Vector(const T* ptr)
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = ptr[i];
            }
        }

        constexpr Vector(const Vector<N, T>& v)
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = v.data[i];
            }
        }

        constexpr Vector(const std::initializer_list<T>& v)
        {
            auto it = v.begin();
            for (size_t i = 0; i < N; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T& operator[](size_t i)
        {
            assert(i < N);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < N);
            return data[i];
        }

        constexpr T Dot(const Vector& v) const
        {
            T temp;
            for (size_t i = 0; i < N; i++)
            {
                temp += data[i] * v[i];
            }
            return temp;
        }
    };

    template<typename T>
    struct Vector<2, T>
    {
        union
        {
            struct
            {
                T x, y;
            };
            T data[2];
        };

        constexpr Vector() : x(0), y(0) {}

        constexpr explicit Vector(T val) : x(val), y(val) {}

        constexpr Vector(T v1, T v2, T v3) : x(v1), y(v2) {}

        constexpr Vector(const std::initializer_list<T>& list)
        {
            auto it = list.begin();
            for (size_t i = 0; i < 2; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T& operator[](size_t i)
        {
            assert(i < 2);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < 2);
            return data[i];
        }

        constexpr T Length() const { return std::sqrt(x * x + y * y); }

        constexpr T Dot(const Vector& v) const { return x * v.x + y * v.y; }

        constexpr T MaxValue() const { return std::max(x, y); }

        constexpr T MinValue() const { return std::min(x, y); }
    };

    template<typename T>
    struct Vector<3, T>
    {
        union
        {
            struct
            {
                T x, y, z;
            };
            T data[3];
        };

        constexpr Vector() : x(0), y(0), z(0) {}

        constexpr explicit Vector(T val) : x(val), y(val), z(val) {}

        constexpr Vector(T v1, T v2, T v3) : x(v1), y(v2), z(v3) {}

        constexpr Vector(const std::initializer_list<T>& list)
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

        constexpr T Length() const { return std::sqrt(x * x + y * y + z * z); }

        constexpr T Dot(const Vector& v) const { return x * v.x + y * v.y + z * v.z; }

        constexpr Vector Cross(const Vector& v) { return {y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y}; }

        constexpr Vector Normalized() const { return (*this) / Length(); }

        constexpr void Normalize() { (*this) /= Length(); }

        constexpr T MaxValue() const { return std::max(std::max(x, y), z); }

        constexpr T MinValue() const { return std::min(std::min(x, y), z); }
    };

    template<typename T>
    struct Vector<4, T>
    {
        union
        {
            struct
            {
                T x, y, z, w;
            };
            T data[4];
        };

        constexpr Vector() : x(0), y(0), z(0), w(0) {}

        constexpr explicit Vector(T val) : x(val), y(val), z(val), w(val) {}

        constexpr Vector(T v1, T v2, T v3, T v4) : x(v1), y(v2), z(v3), w(v4) {}

        constexpr Vector(const std::initializer_list<T>& list)
        {
            auto it = list.begin();
            for (size_t i = 0; i < 4; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T& operator[](size_t i)
        {
            assert(i < 4);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < 4);
            return data[i];
        }

        constexpr T Dot(const Vector& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }
    };


    //取反
    template<size_t N, typename T>
    constexpr Vector<N, T> operator-(const Vector<N, T>& v)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = -v[i];
        }
        return temp;
    }

    //四则运算
    template<size_t N, typename T>
    constexpr Vector<N, T> operator+(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = v1[i] + v2[i];
        }
        return temp;
    }

    template<size_t N, typename T>
    constexpr Vector<N, T> operator-(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = v1[i] - v2[i];
        }
        return temp;
    }

    template<size_t N, typename T>
    constexpr Vector<N, T> operator*(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = v1[i] * v2[i];
        }
        return temp;
    }

    template<size_t N, typename T>
    constexpr Vector<N, T> operator/(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = v1[i] / v2[i];
        }
        return temp;
    }

    //赋值四则运算
    template<size_t N, typename T>
    constexpr Vector<N, T>& operator+=(Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        for (size_t i = 0; i < N; i++)
        {
            v1[i] += v2[i];
        }
        return v1;
    }

    template<size_t N, typename T>
    constexpr Vector<N, T>& operator-=(Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        for (size_t i = 0; i < N; i++)
        {
            v1[i] -= v2[i];
        }
        return v1;
    }

    template<size_t N, typename T>
    constexpr Vector<N, T>& operator*=(Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        for (size_t i = 0; i < N; i++)
        {
            v1[i] *= v2[i];
        }
        return v1;
    }

    template<size_t N, typename T>
    constexpr Vector<N, T>& operator/=(Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        for (size_t i = 0; i < N; i++)
        {
            v1[i] /= v2[i];
        }
        return v1;
    }

    //数乘
    template<size_t N, typename T>
    constexpr Vector<N, T> operator*(const Vector<N, T>& v, T k)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = v[i] * k;
        }
        return temp;
    }

    template<size_t N, typename T>
    constexpr Vector<N, T> operator*(T k, const Vector<N, T>& v)
    {
        return v * k;
    }

    template<size_t N, typename T>
    constexpr Vector<N, T> operator/(const Vector<N, T>& v, T k)
    {
        return v * (1 / k);
    }

    //比较
    template<size_t N, typename T>
    constexpr bool operator>(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= v1[i] > v2[i];
        }
        return flag;
    }

    template<size_t N, typename T>
    constexpr bool operator>=(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= v1[i] >= v2[i];
        }
        return flag;
    }

    template<size_t N, typename T>
    constexpr bool operator<(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= v1[i] < v2[i];
        }
        return flag;
    }

    template<size_t N, typename T>
    constexpr bool operator<=(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= v1[i] <= v2[i];
        }
        return flag;
    }

    //各维度最小值
    template<size_t N, typename T>
    constexpr Vector<N, T> MinVector(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        Vector<N, T> min;
        for (size_t i = 0; i < N; ++i)
        {
            min[i] = std::min(v1[i], v2[i]);
        }
        return min;
    }

    //各维度最大值
    template<size_t N, typename T>
    constexpr Vector<N, T> MaxVector(const Vector<N, T>& v1, const Vector<N, T>& v2)
    {
        Vector<N, T> max;
        for (size_t i = 0; i < N; ++i)
        {
            max[i] = std::max(v1[i], v2[i]);
        }
        return max;
    }

    //输出
    template<size_t N, typename T>
    std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v)
    {
        os << "(";
        for (int i = 0; i < N; ++i)
        {
            os << v[i] << (i < N - 1 ? "," : "");

        }
        return os << ")";
    }

    using Vector4f = Vector<4, float>;
    using Vector3f = Vector<3, float>;
    using Vector2f = Vector<2, float>;
}