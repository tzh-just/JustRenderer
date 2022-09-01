#pragma once

#include "Global.h"

namespace Just {
    template<size_t N, typename T>
    struct Vector {
        T data[N];

        Vector() { for (size_t i = 0; i < N; i++) data[i] = T(); }

        explicit Vector(const T* ptr) {
            for (size_t i = 0; i < N; i++) {
                data[i] = ptr[i];
            }
        }

        Vector(const Vector<N, T>& v) {
            for (size_t i = 0; i < N; i++) {
                data[i] = v.data[i];
            }
        }

        Vector(const std::initializer_list<T>& v) {
            auto it = v.begin();
            for (size_t i = 0; i < N; i++) {
                data[i] = *it++;
            }
        }

        T& operator[](size_t i) {
            assert(i < N);
            return data[i];
        }

        T operator[](size_t i) const {
            assert(i < N);
            return data[i];
        }

        static T Dot(const Vector& v1, const Vector& v2) {
            T temp;
            for (size_t i = 0; i < N; i++) {
                temp += v1[i] * v2[i];
            }
            return temp;
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

        Vector<2, T>() : x(T()), y(T()) {}

        explicit Vector<2, T>(T val) : x(val), y(val) {}

        Vector<2, T>(T a, T b) : x(a), y(b) {}

        T& operator[](size_t i) {
            assert(i < 2);
            return data[i];
        }

        T operator[](size_t i) const {
            assert(i < 2);
            return data[i];
        }

        T Length() const { return std::sqrt(x * x + y * y); }

        static T Dot(const Vector<2, T>& v1, const Vector<2, T>& v2) {
            return v1.x * v2.y + v1.y * v2.x;
        }
    };

    template<typename T>
    struct Vector<3, T> {
        union {
            struct {
                T x, y, z;
            };
            struct {
                T r, g, b;
            };
            T data[3];
        };

        Vector<3, T>() : x(T()), y(T()), z(T()) {}

        explicit Vector<3, T>(T val) : x(val), y(val), z(val) {}

        Vector<3, T>(T a, T b, T c) : x(a), y(b), z(c) {}

        T& operator[](size_t i) {
            assert(i < 3);
            return data[i];
        }

        T operator[](size_t i) const {
            assert(i < 3);
            return data[i];
        }

        //向量长度
        T Length() const { return std::sqrt(x * x + y * y + z * z); }

        //向量归一化
        static Vector<3, T> Normalize(const Vector<3, T>& v) { return v / v.Length(); }

        //向量点乘
        static T Dot(const Vector<3, T>& v1, const Vector<3, T>& v2) {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        }

        //向量叉乘
        static Vector<3, T> Cross(const Vector<3, T>& v1, const Vector<3, T>& v2) {
            return {v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v2.z * v1.x, v1.x * v2.y - v2.x * v1.y};
        }

        //向量最小坐标值
        static T MinComponent(const Vector<3, T>& v) { return std::min(std::min(v.x, v.y), v.z); }

        //向量最大坐标值
        static T MaxComponent(const Vector<3, T>& v) { return std::max(std::max(v.x, v.y), v.z); }

        //向量最大分量索引
        static int MaxDimension(const Vector<3, T>& v) {
            return (v.x < v.y) ? ((v.x < v.z) ? 0 : 2) : ((v.y < v.z) ? 1 : 2);
        }

        //各维度最小值
        static Vector<3, T> Min(const Vector<3, T>& v1, const Vector<3, T>& v2) {
            return Vector<3, T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z));
        }

        //各维度最大值
        static Vector<3, T> Max(const Vector<3, T>& v1, const Vector<3, T>& v2) {
            return Vector<3, T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z));
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

        Vector() : x(T()), y(T()), z(T()), w(T()) {}

        explicit Vector(T val) : x(val), y(val), z(val), w(val) {}

        Vector(T a, T b, T c, T d) : x(a), y(b), z(c), w(d) {}

        T& operator[](size_t i) {
            assert(i < 4);
            return data[i];
        }

        T operator[](size_t i) const {
            assert(i < 4);
            return data[i];
        }

        static T Dot(const Vector<4, T>& v1, const Vector<4, T>& v2) {
            return v1.x * v2.x + v1.y * v1.a.y + v1.z * v1.a.z + v1.w * v1.w;
        }
    };

    //v=-a
    template<size_t N, typename T>
    Vector<N, T> operator-(const Vector<N, T>& v) {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++) {
            temp[i] = -v[i];
        }
        return temp;
    }

    //v=a+b
    template<size_t N, typename T>
    Vector<N, T> operator+(const Vector<N, T>& v1, const Vector<N, T>& v2) {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++) {
            temp[i] = v1[i] + v2[i];
        }
        return temp;
    }

    //v=a-b
    template<size_t N, typename T>
    Vector<N, T> operator-(const Vector<N, T>& v1, const Vector<N, T>& v2) {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++) {
            temp[i] = v1[i] - v2[i];
        }
        return temp;
    }

    //v=a*b
    template<size_t N, typename T>
    Vector<N, T> operator*(const Vector<N, T>& v1, const Vector<N, T>& v2) {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++) {
            temp[i] = v1[i] * v2[i];
        }
        return temp;
    }

    //v=a/b
    template<size_t N, typename T>
    Vector<N, T> operator/(const Vector<N, T>& v1, const Vector<N, T>& v2) {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++) {
            temp[i] = v1[i] / v2[i];
        }
        return temp;
    }

    //a+=b
    template<size_t N, typename T>
    Vector<N, T>& operator+=(Vector<N, T>& v1, const Vector<N, T>& v2) {
        for (size_t i = 0; i < N; i++) {
            v1[i] += v2[i];
        }
        return v1;
    }

    //a-=b
    template<size_t N, typename T>
    Vector<N, T>& operator-=(Vector<N, T>& v1, const Vector<N, T>& v2) {
        for (size_t i = 0; i < N; i++) {
            v1[i] -= v2[i];
        }
        return v1;
    }

    //a*=b
    template<size_t N, typename T>
    Vector<N, T>& operator*=(Vector<N, T>& v1, const Vector<N, T>& v2) {
        for (size_t i = 0; i < N; i++) {
            v1[i] *= v2[i];
        }
        return v1;
    }

    //a/=b
    template<size_t N, typename T>
    Vector<N, T>& operator/=(Vector<N, T>& v1, const Vector<N, T>& v2) {
        for (size_t i = 0; i < N; i++) {
            v1[i] /= v2[i];
        }
        return v1;
    }

    //v=a*k
    template<size_t N, typename T>
    Vector<N, T> operator*(const Vector<N, T>& v1, T k) {
        Vector<N, T> temp;
        for (size_t i = 0; i < N; i++) {
            temp[i] = v1[i] * k;
        }
        return temp;
    }

    //v=k*a
    template<size_t N, typename T>
    Vector<N, T> operator*(T k, const Vector<N, T>& v) {
        return v * k;
    }

    //v=a/k
    template<size_t N, typename T>
    Vector<N, T> operator/(const Vector<N, T>& v, T k) {
        return v * (1 / k);
    }

    //a>b
    template<size_t N, typename T>
    bool operator>(const Vector<N, T>& v1, const Vector<N, T>& v2) {
        bool flag = true;
        for (size_t i = 0; i < N; i++) {
            flag &= v1[i] > v2[i];
        }
        return flag;
    }

    //a>=b
    template<size_t N, typename T>
    bool operator>=(const Vector<N, T>& v1, const Vector<N, T>& v2) {
        bool flag = true;
        for (size_t i = 0; i < N; i++) {
            flag &= v1[i] >= v2[i];
        }
        return flag;
    }

    //a<b
    template<size_t N, typename T>
    bool operator<(const Vector<N, T>& v1, const Vector<N, T>& v2) {
        bool flag = true;
        for (size_t i = 0; i < N; i++) {
            flag &= v1[i] < v2[i];
        }
        return flag;
    }

    //a<=b
    template<size_t N, typename T>
    bool operator<=(const Vector<N, T>& v1, const Vector<N, T>& v2) {
        bool flag = true;
        for (size_t i = 0; i < N; i++) {
            flag &= v1[i] <= v2[i];
        }
        return flag;
    }

    template<size_t N, typename T>
    std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v) {
        os << "(";
        for (int i = 0; i < N; ++i) {
            os << v[i] << (i < N - 1 ? "," : "");

        }
        return os << ")";
    }

    using Vector4f = Vector<4, float>;
    using Vector3f = Vector<3, float>;
    using Normal3f = Vector<3, float>;
    using Vector2f = Vector<2, float>;

    template<size_t N, typename T>
    using Point = Vector<N, T>;
    using Point4f = Point<4, float>;
    using Point3f = Point<3, float>;
    using Point2f = Point<2, float>;
    using Point2i = Point<2, int>;

    template<size_t N, typename T>
    using Color = Vector<N, T>;
    using Color4i = Color<4, int>;
    using Color3i = Color<3, int>;
    using Spectrum = Color<3, float>;

    template<size_t N, typename T>
    using Tuple = Vector<N, T>;
    using Tuple3f = Tuple<3, float>;
    using Tuple3i = Tuple<3, int>;
    using Tuple2f = Tuple<2, float>;
    using Tuple2i = Tuple<2, int>;
}