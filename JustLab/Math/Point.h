//================================================
// 坐标
//================================================

#pragma once

#include "Global.h"
#include "Vector.h"

namespace Just
{

    //坐标模板类
    //-----------------------------------------------------------------------------
    template<size_t N, typename T>
    struct Point
    {
        T data[N];

        constexpr Point() { for (size_t i = 0; i < N; i++) data[i] = T(); }

        constexpr Point(const T *ptr)
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = ptr[i];
            }
        }

        constexpr Point(const Point<N, T> &p1)
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = p1.data[i];
            }
        }

        constexpr Point(const std::initializer_list<T> &p1)
        {
            auto it = p1.begin();
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

    //特化二维坐标
    //-----------------------------------------------------------------------------
    template<typename T>
    struct Point<2, T>
    {
        union
        {
            struct
            {
                T x, y;
            };
            T data[2];
        };

        constexpr Point() : x(0), y(0) {}

        constexpr explicit Point(T val) : x(val), y(val) {}

        constexpr Point(T x, T y) : x(x), y(y) {}

        constexpr Point(const std::initializer_list<T> &list)
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

        constexpr T Dot(const Point &p) const { return x * p.x + y * p.y; }
    };

    //特化三维坐标
    //-----------------------------------------------------------------------------
    template<typename T>
    struct Point<3, T>
    {
        union
        {
            struct
            {
                T x, y, z;
            };
            T data[3];
        };

        constexpr Point() : x(0), y(0), z(0) {}

        constexpr explicit Point(T val) : x(val), y(val), z(val) {}

        constexpr Point(T x, T y, T c) : x(x), y(y), z(c) {}

        constexpr Point(const std::initializer_list<T> &list)
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

        constexpr T Dot(const Point &p) const { return x * p.x + y * p.y + z * p.z; }
    };

    //特化齐次坐标
    //-----------------------------------------------------------------------------
    template<typename T>
    struct Point<4, T>
    {
        union
        {
            struct
            {
                T x, y, z, w;
            };
            T data[4];
        };

        constexpr Point() : x(0), y(0), z(0), w(0) {}

        constexpr explicit Point(T val) : x(val), y(val), z(val), w(val) {}

        constexpr Point(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

        constexpr Point(const std::initializer_list<T> &list)
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

        constexpr T Dot(const Point &p) const { return x * p.x + y * p.y + z * p.z + w * p.w; }
    };


    //坐标重载方法
    //-----------------------------------------------------------------------------
    //-p
    template<size_t N, typename T>
    constexpr Point<N, T> operator-(const Point<N, T> &p)
    {
        Point<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = -p[i];
        }
        return temp;
    }

    //p1+p2
    template<size_t N, typename T>
    constexpr Point<N, T> operator+(const Point<N, T> &p1, const Point<N, T> &p2)
    {
        Point<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = p1[i] + p2[i];
        }
        return temp;
    }

    //p+v
    template<size_t N, typename T>
    constexpr Point<N, T> operator+(const Point<N, T> &p, const Vector<N, T> &v)
    {
        Point<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = p[i] + v[i];
        }
        return temp;
    }

    //p1-p2
    template<size_t N, typename T>
    constexpr Vector<N, T> operator-(const Point<N, T> &p1, const Point<N, T> &p2)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = p1[i] - p2[i];
        }
        return temp;
    }

    //p-v
    template<size_t N, typename T>
    constexpr Vector<N, T> operator-(const Point<N, T> &p, const Vector<N, T> &v)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = p[i] - v[i];
        }
        return temp;
    }

    //p*k
    template<size_t N, typename T>
    constexpr Point<N, T> operator*(const Point<N, T> &p, T k)
    {
        Point<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = p[i] * k;
        }
        return temp;
    }

    //k*p
    template<size_t N, typename T>
    constexpr Point<N, T> operator*(T k, const Point<N, T> &p)
    {
        return p * k;
    }

    //p/k
    template<size_t N, typename T>
    constexpr Point<N, T> operator/(const Point<N, T> &p, T k)
    {
        return p * (1 / k);
    }

    //p1>p2
    template<size_t N, typename T>
    constexpr bool operator>(const Point<N, T> &p1, const Point<N, T> &p2)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= p1[i] > p2[i];
        }
        return flag;
    }

    //p1>=p2
    template<size_t N, typename T>
    constexpr bool operator>=(const Point<N, T> &p1, const Point<N, T> &p2)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= p1[i] >= p2[i];
        }
        return flag;
    }

    //p1<p2
    template<size_t N, typename T>
    constexpr bool operator<(const Point<N, T> &p1, const Point<N, T> &p2)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= p1[i] < p2[i];
        }
        return flag;
    }

    //p1<=p2
    template<size_t N, typename T>
    constexpr bool operator<=(const Point<N, T> &p1, const Point<N, T> &p2)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= p1[i] <= p2[i];
        }
        return flag;
    }

    //坐标扩展方法
    //-----------------------------------------------------------------------------
    //两坐标取各维度最小值
    template<size_t N, typename T>
    constexpr Point<N, T> MinPoint(const Point<N, T> &p1, const Point<N, T> &p2)
    {
        Point<N, T> min;
        for (size_t i = 0; i < N; ++i)
        {
            min[i] = std::min(p1[i], p2[i]);
        }
        return min;
    }

    //两坐标取各维度最大值
    template<size_t N, typename T>
    constexpr Point<N, T> MaxPoint(const Point<N, T> &p1, const Point<N, T> &p2)
    {
        Point<N, T> max;
        for (size_t i = 0; i < N; ++i)
        {
            max[i] = std::max(p1[i], p2[i]);
        }
        return max;
    }

    //取各维度中最小值
    template<size_t N, typename T>
    constexpr Point<N, T> MinValue(const Point<N, T> &p)
    {
        T min = p[0];
        for (size_t i = 1; i < N; ++i)
        {
            min = std::min(min, p[i]);
        }
        return min;
    }

    //取各维度中最大值
    template<size_t N, typename T>
    constexpr Point<N, T> MaxValue(const Point<N, T> &p)
    {
        T max = p[0];
        for (size_t i = 1; i < N; ++i)
        {
            max = std::max(max, p[i]);
        }
        return max;
    }

    //输出
    template<size_t N, typename T>
    std::ostream &operator<<(std::ostream &os, const Point<N, T> &p)
    {
        os << "(";
        for (int i = 0; i < N; ++i)
        {
            os << p[i] << (i < N - 1 ? "," : "");

        }
        return os << ")";
    }

    //坐标别名
    //-----------------------------------------------------------------------------
    using Point4f = Point<4, float>;
    using Point3f = Point<3, float>;
    using Point2f = Point<2, float>;
}