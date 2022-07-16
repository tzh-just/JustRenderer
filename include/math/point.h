//================================================
// 点坐标
//
//================================================

#pragma once

#include "definition.h"

namespace Just {
    template<size_t N, typename T>
    struct Point {
        T data[N];

        Point() { for (size_t i = 0; i < N; i++)data[i] = T(); }

        Point(const Point<N, T> &other) { for (size_t i = 0; i < N; i++)data[i] = other.data[i]; }

        Point(const std::initializer_list<T> &list) {
            auto it = list.begin();
            for (size_t i = 0; i < N; i++)
                data[i] = *it++;
        }

        T &operator[](size_t i) {
            assert(i < N);
            return data[i];
        }

        const T &operator[](size_t i) const {
            assert(i < N);
            return data[i];
        }
    };

    template<typename T>
    struct Point<2, T> {
        union {
            struct {
                T x, y;
            };
            T data[2];
        };

        //缺省构造函数
        Point() : x(T()), y(T()) {}

        //有参构造函数
        explicit Point(T value) : x(value), y(value) {}

        Point(T v1, T v2) : x(v1), y(v2) {}

        //拷贝构造函数
        Point(const Point &other) = default;

        //拷贝赋值运算符重载
        Point &operator=(const Point &other) = default;

        //析构函数
        ~Point() = default;

        //索引操作符重载
        T &operator[](size_t i) {
            assert(i < 2);
            return data[i];
        }

        const T &operator[](size_t i) const {
            assert(i < 2);
            return data[i];
        }
    };

    template<typename T>
    struct Point<3, T> {
        union {
            struct {
                T x, y, z;
            };
            T data[3];
        };

        //缺省构造函数
        Point() : x(T()), y(T()), z(T()) {}

        //有参构造函数
        explicit Point(T value) : x(value), y(value), z(value) {}

        Point(T v1, T v2, T v3) : x(v1), y(v2), z(v3) {}

        //拷贝构造函数
        Point(const Point &other) = default;

        //拷贝赋值运算符重载
        Point &operator=(const Point &other) = default;

        //析构函数
        ~Point() = default;

        //索引操作符重载
        T &operator[](size_t i) {
            assert(i < 3);
            return data[i];
        }

        const T &operator[](size_t i) const {
            assert(i < 3);
            return data[i];
        }
    };

    template<typename T>
    struct Point<4, T> {
        union {
            struct {
                T x, y, z, w;
            };
            T data[4];
        };

        //缺省构造函数
        Point() : x(T()), y(T()), z(T()), w(1) {}

        //有参构造函数
        explicit Point(T value) : x(value), y(value), z(value), w(1) {}

        Point(T v1, T v2, T v3) : x(v1), y(v2), z(v3), w(1) {}

        explicit Point(Point<3,T> p) : x(p.x), y(p.y), z(p.z), w(1) {}

        Point(T v1, T v2, T v3, T v4) : x(v1), y(v2), z(v3), w(v4) {}

        Point(Point<3,T> p, T v4) : x(p.x), y(p.y), z(p.z), w(v4) {}

        //拷贝构造函数
        Point(const Point &other) = default;

        //拷贝赋值运算符重载
        Point &operator=(const Point &other) = default;

        //索引操作符重载
        T &operator[](size_t i) {
            assert(i < 4);
            return data[i];
        }

        const T &operator[](size_t i) const {
            assert(i < 4);
            return data[i];
        }
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    template<size_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Point<N, T> &p) {
        os << "(";
        for (size_t i = 0; i < N; i++) {
            os << p.data[i];
            if (i + 1 != N)
                os << ",";
        }
        os << ")";
        return os;
    }

    using Point2f = Point<2, float>;
    using Point3f = Point<3, float>;
    using Point4f = Point<4, float>;
}