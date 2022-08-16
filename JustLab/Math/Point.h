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

        constexpr Point(const T* ptr)
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = ptr[i];
            }
        }

        constexpr Point(const Point<N, T>& a)
        {
            for (size_t i = 0; i < N; i++)
            {
                data[i] = a.data[i];
            }
        }

        constexpr Point(const std::initializer_list<T>& a)
        {
            auto it = a.begin();
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

        constexpr Point(T a, T b) : x(a), y(b) {}

        constexpr Point(const std::initializer_list<T>& list)
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
        
        constexpr T Dot(const Point& a) const { return x * a.x + y * a.y; }
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

        constexpr Point(T a, T b, T c) : x(a), y(b), z(c) {}

        constexpr Point(const std::initializer_list<T>& list)
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
        
        constexpr T Dot(const Point& a) const { return x * a.x + y * a.y + z * a.z; }
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

        constexpr Point(T a, T b, T c, T d) : x(a), y(b), z(c), w(d) {}

        constexpr Point(const std::initializer_list<T>& list)
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

        constexpr T Dot(const Point& a) const { return x * a.x + y * a.y + z * a.z + w * a.w; }
    };


    //坐标重载方法
    //-----------------------------------------------------------------------------
    //p=-a
    template<size_t N, typename T>
    constexpr Point<N, T> operator-(const Point<N, T>& a)
    {
        Point<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = -a[i];
        }
        return temp;
    }

    //p=a+b
    template<size_t N, typename T>
    constexpr Point<N, T> operator+(const Point<N, T>& a, const Point<N, T>& b)
    {
        Point<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] + b[i];
        }
        return temp;
    }

    //v=a-b
    template<size_t N, typename T>
    constexpr Vector<N, T> operator-(const Point<N, T>& a, const Point<N, T>& b)
    {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] - b[i];
        }
        return temp;
    }

    //p=a*k
    template<size_t N, typename T>
    constexpr Point<N, T> operator*(const Point<N, T>& a, T k)
    {
        Point<N, T> temp;
        for (size_t i = 0; i < N; i++)
        {
            temp[i] = a[i] * k;
        }
        return temp;
    }

    //p=k*a
    template<size_t N, typename T>
    constexpr Point<N, T> operator*(T k, const Point<N, T>& a)
    {
        return a * k;
    }

    //p=a/k
    template<size_t N, typename T>
    constexpr Point<N, T> operator/(const Point<N, T>& a, T k)
    {
        return a * (1 / k);
    }

    //a>b
    template<size_t N, typename T>
    constexpr bool operator>(const Point<N, T>& a, const Point<N, T>& b)
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
    constexpr bool operator>=(const Point<N, T>& a, const Point<N, T>& b)
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
    constexpr bool operator<(const Point<N, T>& a, const Point<N, T>& b)
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
    constexpr bool operator<=(const Point<N, T>& a, const Point<N, T>& b)
    {
        bool flag = true;
        for (size_t i = 0; i < N; i++)
        {
            flag &= a[i] <= b[i];
        }
        return flag;
    }

    //坐标扩展方法
    //-----------------------------------------------------------------------------
    //各维度最小值
    template<size_t N, typename T>
    constexpr Point<N, T> MinPoint(const Point<N, T>& a, const Point<N, T>& b)
    {
        Point<N, T> min;
        for (size_t i = 0; i < N; ++i)
        {
            min[i] = std::min(a[i], b[i]);
        }
        return min;
    }

    //各维度最大值
    template<size_t N, typename T>
    constexpr Point<N, T> MaxPoint(const Point<N, T>& a, const Point<N, T>& b)
    {
        Point<N, T> max;
        for (size_t i = 0; i < N; ++i)
        {
            max[i] = std::max(a[i], b[i]);
        }
        return max;
    }

    //输出
    template<size_t N, typename T>
    std::ostream& operator<<(std::ostream& os, const Point<N, T>& a)
    {
        os << "(";
        for (int i = 0; i < N; ++i)
        {
            os << a[i] << (i < N - 1 ? "," : "");

        }
        return os << ")";
    }

    //坐标别名
    //-----------------------------------------------------------------------------
    using Point4f = Point<4, float>;
    using Point3f = Point<3, float>;
    using Point2f = Point<2, float>;
}