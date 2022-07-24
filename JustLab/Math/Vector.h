//================================================
// 矢量模板
//================================================

#pragma once

#include "../Global.h"

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

        Vector() : x(T()), y(T()) {}

        Vector(T v1, T v2) : x(v1), y(v2) {}

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

        Vector() : x(0), y(0), z(0) {}

        Vector(T v1, T v2, T v3) : x(v1), y(v2), z(v3) {}

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
    struct Vector<4, T> {
        union {
            struct {
                T x, y, z, w;
            };
            T data[4];
        };

        Vector() : x(0), y(0), z(0), w(0) {}

        Vector(T v1, T v2, T v3, T v4) : x(v1), y(v2), z(v3), w(v4) {}

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

    using Vector2f = Vector<2, float>;
    using Vector3f = Vector<3, float>;
}


