#pragma once

#include "Global.h"

namespace Just
{

    //矢量模板类
    //-----------------------------------------------------------------------------
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

    //特化二维矢量
    //-----------------------------------------------------------------------------
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

        constexpr Vector(T x, T y) : x(x), y(y) {}

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
    };

    //特化三维矢量
    //-----------------------------------------------------------------------------
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

        constexpr Vector(T x, T y, T z) : x(x), y(y), z(z) {}

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
    };

    //特化四维矢量
    //-----------------------------------------------------------------------------
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

        constexpr Vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

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


    //矢量重载方法
    //-----------------------------------------------------------------------------
    //v=-a
    template<size_t N, typename T>
    constexpr Vector<N, T> operator-(const Vector<N, T>& a)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = -a[i];
        }
        return temp;
    }

    //v=a+b
    template<size_t N, typename T>
    constexpr Vector<N, T> operator+(const Vector<N, T>& a, const Vector<N, T>& b)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] + b[i];
        }
        return temp;
    }

    //v=a-b
    template<size_t N, typename T>
    constexpr Vector<N, T> operator-(const Vector<N, T>& a, const Vector<N, T>& b)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] - b[i];
        }
        return temp;
    }

    //v=a*b
    template<size_t N, typename T>
    constexpr Vector<N, T> operator*(const Vector<N, T>& a, const Vector<N, T>& b)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] * b[i];
        }
        return temp;
    }

    //v=a/b
    template<size_t N, typename T>
    constexpr Vector<N, T> operator/(const Vector<N, T>& a, const Vector<N, T>& b)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] / b[i];
        }
        return temp;
    }

    //a+=b
    template<size_t N, typename T>
    constexpr Vector<N, T>& operator+=(Vector<N, T>& a, const Vector<N, T>& b)
    {
        for (size_t i = 0; i < N; i++)
        {
            a[i] += b[i];
        }
        return a;
    }

    //a-=b
    template<size_t N, typename T>
    constexpr Vector<N, T>& operator-=(Vector<N, T>& a, const Vector<N, T>& b)
    {
        for (size_t i = 0; i < N; i++)
        {
            a[i] -= b[i];
        }
        return a;
    }

    //a*=b
    template<size_t N, typename T>
    constexpr Vector<N, T>& operator*=(Vector<N, T>& a, const Vector<N, T>& b)
    {
        for (size_t i = 0; i < N; i++)
        {
            a[i] *= b[i];
        }
        return a;
    }

    //a/=b
    template<size_t N, typename T>
    constexpr Vector<N, T>& operator/=(Vector<N, T>& a, const Vector<N, T>& b)
    {
        for (size_t i = 0; i < N; i++)
        {
            a[i] /= b[i];
        }
        return a;
    }

    //v=a*k
    template<size_t N, typename T>
    constexpr Vector<N, T> operator*(const Vector<N, T>& a, T k)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] * k;
        }
        return temp;
    }

    //v=k*a
    template<size_t N, typename T>
    constexpr Vector<N, T> operator*(T k, const Vector<N, T>& a)
    {
        return a * k;
    }

    //v=a/k
    template<size_t N, typename T>
    constexpr Vector<N, T> operator/(const Vector<N, T>& a, T k)
    {
        return a * (1 / k);
    }

    //a>b
    template<size_t N, typename T>
    constexpr bool operator>(const Vector<N, T>& a, const Vector<N, T>& b)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= a[i] > b[i];
        }
        return flag;
    }

    //a>=b
    template<size_t N, typename T>
    constexpr bool operator>=(const Vector<N, T>& a, const Vector<N, T>& b)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= a[i] >= b[i];
        }
        return flag;
    }

    //a<b
    template<size_t N, typename T>
    constexpr bool operator<(const Vector<N, T>& a, const Vector<N, T>& b)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= a[i] < b[i];
        }
        return flag;
    }

    //a<=b
    template<size_t N, typename T>
    constexpr bool operator<=(const Vector<N, T>& a, const Vector<N, T>& b)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= a[i] <= b[i];
        }
        return flag;
    }

    //矢量扩展方法
    //-----------------------------------------------------------------------------
    //各维度最小值
    template<size_t N, typename T>
    constexpr Vector<N, T> MinVector(const Vector<N, T>& a, const Vector<N, T>& b)
    {
        Vector<N, T> min;
        for (size_t i = 0; i < N; ++i)
        {
            min[i] = std::min(a[i], b[i]);
        }
        return min;
    }

    //各维度最大值
    template<size_t N, typename T>
    constexpr Vector<N, T> MaxVector(const Vector<N, T>& a, const Vector<N, T>& b)
    {
        Vector<N, T> max;
        for (size_t i = 0; i < N; ++i)
        {
            max[i] = std::max(a[i], b[i]);
        }
        return max;
    }

    //输出
    template<size_t N, typename T>
    std::ostream& operator<<(std::ostream& os, const Vector<N, T>& a)
    {
        os << "(";
        for (int i = 0; i < N; ++i)
        {
            os << a[i] << (i < N - 1 ? "," : "");

        }
        return os << ")";
    }

    //矢量别名
    //-----------------------------------------------------------------------------
    using Vector4f = Vector<4, float>;
    using Vector3f = Vector<3, float>;
    using Point2f = Vector<2, float>;
}