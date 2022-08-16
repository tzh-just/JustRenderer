#pragma once

#include "Global.h"

namespace Just
{

    //颜色模板类
    //-----------------------------------------------------------------------------
    template<size_t N, typename T>
    struct Color
    {
        T data[N];

        constexpr Color() { for (size_t i = 0; i < N; i++) data[i] = T(); }

        constexpr Color(const T *ptr)
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = ptr[i];
            }
        }

        constexpr Color(const Color<N, T> &a)
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = a.data[i];
            }
        }

        constexpr Color(const std::initializer_list<T> &a)
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

        constexpr T Dot(const Color &a) const
        {
            T temp;
            for (size_t i = 0; i < N; i++)
            {
                temp += data[i] * a[i];
            }
            return temp;
        }
    };

    //特化RGB颜色
    //-----------------------------------------------------------------------------
    template<typename T>
    struct Color<3, T>
    {
        union
        {
            struct
            {
                T r, g, b;
            };
            T data[3];
        };

        constexpr Color() : r(0), g(0), b(0) {}

        constexpr explicit Color(T val) : r(val), g(val), b(val) {}

        constexpr Color(T r, T g, T b) : r(r), g(g), b(b) {}

        constexpr Color(const std::initializer_list<T> &list)
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

        constexpr T GrayScale() const
        {
            return 0.299f * r + 0.587f * g + 0.114f * b;
        }
    };

    //特化RGBA颜色
    //-----------------------------------------------------------------------------
    template<typename T>
    struct Color<4, T>
    {
        union
        {
            struct
            {
                T r, g, b, a;
            };
            T data[4];
        };

        constexpr Color() : r(0), g(0), b(0), a(0) {}

        constexpr explicit Color(T val) : r(val), g(val), b(val), a(val) {}

        constexpr Color(T r, T g, T b, T a) : r(r), g(g), b(b), a(a) {}

        constexpr Color(const std::initializer_list<T> &list)
        {
            auto it = list.begin();
            for (size_t i = 0; i < 4; i++)
            {
                data[i] = *it++;
            }
        }

        constexpr T &operator[](size_t i)
        {
            assert(i < 4);
            return data[i];
        }

        constexpr T operator[](size_t i) const
        {
            assert(i < 4);
            return data[i];
        }
    };


    //颜色重载方法
    //-----------------------------------------------------------------------------
    //v=a+b
    template<size_t N, typename T>
    constexpr Color<N, T> operator+(const Color<N, T> &a, const Color<N, T> &b)
    {
        Color<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] + b[i];
        }
        return temp;
    }

    //v=a-b
    template<size_t N, typename T>
    constexpr Color<N, T> operator-(const Color<N, T> &a, const Color<N, T> &b)
    {
        Color<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] - b[i];
        }
        return temp;
    }

    //v=a*b
    template<size_t N, typename T>
    constexpr Color<N, T> operator*(const Color<N, T> &a, const Color<N, T> &b)
    {
        Color<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] * b[i];
        }
        return temp;
    }

    //v=a/b
    template<size_t N, typename T>
    constexpr Color<N, T> operator/(const Color<N, T> &a, const Color<N, T> &b)
    {
        Color<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] / b[i];
        }
        return temp;
    }

    //a+=b
    template<size_t N, typename T>
    constexpr Color<N, T> &operator+=(Color<N, T> &a, const Color<N, T> &b)
    {
        for (size_t i = 0; i < N; i++)
        {
            a[i] += b[i];
        }
        return a;
    }

    //a-=b
    template<size_t N, typename T>
    constexpr Color<N, T> &operator-=(Color<N, T> &a, const Color<N, T> &b)
    {
        for (size_t i = 0; i < N; i++)
        {
            a[i] -= b[i];
        }
        return a;
    }

    //a*=b
    template<size_t N, typename T>
    constexpr Color<N, T> &operator*=(Color<N, T> &a, const Color<N, T> &b)
    {
        for (size_t i = 0; i < N; i++)
        {
            a[i] *= b[i];
        }
        return a;
    }

    //a/=b
    template<size_t N, typename T>
    constexpr Color<N, T> &operator/=(Color<N, T> &a, const Color<N, T> &b)
    {
        for (size_t i = 0; i < N; i++)
        {
            a[i] /= b[i];
        }
        return a;
    }

    //v=a*k
    template<size_t N, typename T>
    constexpr Color<N, T> operator*(const Color<N, T> &a, T k)
    {
        Color<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] * k;
        }
        return temp;
    }

    //v=k*a
    template<size_t N, typename T>
    constexpr Color<N, T> operator*(T k, const Color<N, T> &a)
    {
        return a * k;
    }

    //v=a/k
    template<size_t N, typename T>
    constexpr Color<N, T> operator/(const Color<N, T> &a, T k)
    {
        return a * (1 / k);
    }

    //颜色扩展方法
    //-----------------------------------------------------------------------------
    //输出
    template<size_t N, typename T>
    std::ostream &operator<<(std::ostream &os, const Color<N, T> &a)
    {
        os << "(";
        for (int i = 0; i < N; ++i)
        {
            os << a[i] << (i < N - 1 ? "," : "");

        }
        return os << ")";
    }

    //颜色别名
    //-----------------------------------------------------------------------------
    using Color4f = Color<4, float>;
    using Color3f = Color<3, float>;
}