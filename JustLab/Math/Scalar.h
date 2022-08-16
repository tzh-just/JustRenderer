//================================================
// 标量
//================================================

#pragma once

#include "Global.h"
#include "Vector.h"

namespace Just
{

    //标量模板类
    //-----------------------------------------------------------------------------
    template<size_t N, typename T>
    struct Scalar
    {
        T data[N];

        constexpr Scalar() { for (size_t i = 0; i < N; i++) data[i] = T(); }

        constexpr Scalar(const T *ptr)
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = ptr[i];
            }
        }

        constexpr Scalar(const Scalar<N, T> &a)
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = a.data[i];
            }
        }

        constexpr Scalar(const std::initializer_list<T> &a)
        {
            auto it = a.begin();
            for (size_t i = 0; i < N; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T &operator[](size_t i)
        {
            assert(i < N);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < N);
            return data[i];
        }
    };

    //特化二维标量
    //-----------------------------------------------------------------------------
    template<typename T>
    struct Scalar<2, T>
    {
        union
        {
            struct
            {
                T x, y;
            };
            T data[2];
        };

        constexpr Scalar() : x(0), y(0) {}

        constexpr explicit Scalar(T val) : x(val), y(val) {}

        constexpr Scalar(T x, T y) : x(x), y(y) {}

        constexpr Scalar(const std::initializer_list<T> &list)
        {
            auto it = list.begin();
            for (size_t i = 0; i < 2; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T &operator[](size_t i)
        {
            assert(i < 2);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < 2);
            return data[i];
        }
    };

    //特化三维标量
    //-----------------------------------------------------------------------------
    template<typename T>
    struct Scalar<3, T>
    {
        union
        {
            struct
            {
                T x, y, z;
            };
            T data[3];
        };

        constexpr Scalar() : x(0), y(0), z(0) {}

        constexpr explicit Scalar(T val) : x(val), y(val), z(val) {}

        constexpr Scalar(T x, T y, T z) : x(x), y(y), z(z) {}

        constexpr Scalar(const std::initializer_list<T> &list)
        {
            auto it = list.begin();
            for (size_t i = 0; i < 3; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T &operator[](size_t i)
        {
            assert(i < 3);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < 3);
            return data[i];
        }
    };

    //标量重载方法
    //-----------------------------------------------------------------------------
    //s=-a
    template<size_t N, typename T>
    constexpr Scalar<N, T> operator-(const Scalar<N, T> &a)
    {
        Scalar<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = -a[i];
        }
        return temp;
    }

    //s=a+b
    template<size_t N, typename T>
    constexpr Scalar<N, T> operator+(const Scalar<N, T> &a, const Scalar<N, T> &b)
    {
        Scalar<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] + b[i];
        }
        return temp;
    }

    //v=a-b
    template<size_t N, typename T>
    constexpr Vector<N, T> operator-(const Scalar<N, T> &a, const Scalar<N, T> &b)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] - b[i];
        }
        return temp;
    }

    //s=a*k
    template<size_t N, typename T>
    constexpr Scalar<N, T> operator*(const Scalar<N, T> &a, T k)
    {
        Scalar<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] * k;
        }
        return temp;
    }

    //s=k*a
    template<size_t N, typename T>
    constexpr Scalar<N, T> operator*(T k, const Scalar<N, T> &a)
    {
        return a * k;
    }

    //s=a/k
    template<size_t N, typename T>
    constexpr Scalar<N, T> operator/(const Scalar<N, T> &a, T k)
    {
        return a * (1 / k);
    }

    //a>b
    template<size_t N, typename T>
    constexpr bool operator>(const Scalar<N, T> &a, const Scalar<N, T> &b)
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
    constexpr bool operator>=(const Scalar<N, T> &a, const Scalar<N, T> &b)
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
    constexpr bool operator<(const Scalar<N, T> &a, const Scalar<N, T> &b)
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
    constexpr bool operator<=(const Scalar<N, T> &a, const Scalar<N, T> &b)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= a[i] <= b[i];
        }
        return flag;
    }

    //标量扩展方法
    //-----------------------------------------------------------------------------
    //输出
    template<size_t N, typename T>
    std::ostream &operator<<(std::ostream &os, const Scalar<N, T> &a)
    {
        os << "(";
        for (int i = 0; i < N; ++i)
        {
            os << a[i] << (i < N - 1 ? "," : "");

        }
        return os << ")";
    }

    //标量别名
    //-----------------------------------------------------------------------------
    using Scalar4i = Scalar<4, float>;
    using Scalar3i = Scalar<3, float>;
    using Scalar2i = Scalar<2, float>;
}