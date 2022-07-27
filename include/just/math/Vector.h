//================================================
// 矢量模板
//================================================

#pragma once

#include "../Global.h"

namespace Just {

    template<int N, typename T>
    struct Vector {
        T data[N];

        Vector() {
            for (int i = 0; i < N; i++)
                data[i] = 0;
        }

        Vector(const Vector<N, T> &other) {
            for (int i = 0; i < N; i++)
                data[i] = other.data[i];
        }

        Vector(const std::initializer_list<T> &list) {
            auto it = list.begin();
            for (int i = 0; i < N; i++)
                data[i] = *it++;
        }

        T &operator[](int i) {
            assert(i < N);
            return data[i];
        }

        T operator[](int i) const {
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

        Vector() : x(0), y(0) {}

        Vector(T v1, T v2) : x(v1), y(v2) {}

        T &operator[](int i) {
            assert(i < 2);
            return data[i];
        }

        T operator[](int i) const {
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

        T &operator[](int i) {
            assert(i < 3);
            return data[i];
        }

        T operator[](int i) const {
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

        T &operator[](int i) {
            assert(i < 4);
            return data[i];
        }

        T operator[](int i) const {
            assert(i < 4);
            return data[i];
        }

    };

    using Vector2f = Vector<2, float>;
    using Vector3f = Vector<3, float>;
    using Vector4f = Vector<4, float>;
}


