//================================================
// 矢量模板类
// 特化二维矢量
// 特化三维矢量
//================================================

#pragma once

#include "definition.h"

namespace Just {
    template<size_t N, typename T>
    struct Vector {
        T data[N];

        Vector() {
            for (size_t i = 0; i < N; i++)
                data[i] = T();
        }

        Vector(const Vector<N, T> &other) {
            for (size_t i = 0; i < N; i++)
                data[i] = other.data[i];
        }

        Vector(const std::initializer_list<T> &list) {
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
    struct Vector<2, T> {
        union {
            struct {
                T x, y;
            };
            T data[2];
        };

        //缺省构造函数
        Vector() : x(T()), y(T()) {}

        //有参构造函数
        explicit Vector(T value) : x(value), y(value) {}

        Vector(T v1, T v2) : x(v1), y(v2) {}

        //拷贝构造函数
        Vector(const Vector &other) = default;

        //拷贝赋值运算符重载
        Vector &operator=(const Vector &other) = default;

        //析构函数
        ~Vector() = default;

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
    struct Vector<3, T> {
        union {
            struct {
                T x, y, z;
            };
            T data[3];
        };

        //缺省构造函数
        Vector() : x(T()), y(T()), z(T()) {}

        //有参构造函数
        explicit Vector(T value) : x(value), y(value), z(value) {}

        Vector(T v1, T v2, T v3) : x(v1), y(v2), z(v3) {}

        //拷贝构造函数
        Vector(const Vector &other) = default;

        //拷贝赋值运算符重载
        Vector &operator=(const Vector &other) = default;

        //析构函数
        ~Vector() = default;

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


    //输出
    //----------------------------------------------------------------------------------------------------------
    template<size_t N, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Vector<N, T> &v) {
        os << "<";
        for (size_t i = 0; i < N; i++) {
            os << v.data[i];
            if (i + 1 != N)
                os << ",";
        }
        os << ">";
        return os;
    }

    using Vector2f = Vector<2, float>;
    using Vector3f = Vector<3, float>;
}


