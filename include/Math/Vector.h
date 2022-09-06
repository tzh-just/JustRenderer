#pragma once

#include "Global.h"

namespace Just {
template<size_t N, typename T>
struct Vector {
    T data[N];

    Vector() : data(T()) {}

    T& operator[](size_t i) {
        assert(i < N);
        return data[i];
    }

    T operator[](size_t i) const {
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


    explicit Vector(T val) : x(val), y(val) {}

    Vector(T x, T y) : x(x), y(y) {}

    T& operator[](size_t i) {
        assert(i < 2);
        return data[i];
    }

    T operator[](size_t i) const {
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
        struct {
            T r, g, b;
        };
        T data[3];
    };

    Vector() : x(T()), y(T()), z(T()) {}

    explicit Vector(T val) : x(val), y(val), z(val) {}

    Vector(T x, T y, T z) : x(x), y(y), z(z) {}

    T& operator[](size_t i) {
        assert(i < 3);
        return data[i];
    }

    T operator[](size_t i) const {
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

    Vector() : x(T()), y(T()), z(T()), w(T()) {}

    explicit Vector(T val) : x(val), y(val), z(val), w(val) {}

    Vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

    T& operator[](size_t i) {
        assert(i < 4);
        return data[i];
    }

    T operator[](size_t i) const {
        assert(i < 4);
        return data[i];
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

//a*=k
template<size_t N, typename T, typename U>
Vector<N, T>& operator*=(Vector<N, T>& v, U k) {
    for (size_t i = 0; i < N; i++) {
        v[i] *= k;
    }
    return v;
}

//a/=k
template<size_t N, typename T, typename U>
Vector<N, T>& operator/=(Vector<N, T>& v, U k) {
    for (size_t i = 0; i < N; i++) {
        v[i] /= k;
    }
    return v;
}

//v=a*k
template<size_t N, typename T, typename U>
Vector<N, T> operator*(const Vector<N, T>& v, U k) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++) {
        temp[i] = v[i] * k;
    }
    return temp;
}

//v=k*a
template<size_t N, typename T, typename U>
Vector<N, T> operator*(U k, const Vector<N, T>& v) {
    return v * k;
}

//v=a/k
template<size_t N, typename T, typename U>
Vector<N, T> operator/(const Vector<N, T>& v, U k) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++) {
        temp[i] = v[i] / k;
    }
    return temp;
}

template<size_t N, typename T>
std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v) {
    os << "(";
    for (int i = 0; i < N; ++i) {
        os << v[i] << (i < N - 1 ? "," : "");

    }
    return os << ")";
}

//向量绝对值
template<size_t N, typename T>
Vector<N, T> Abs(const Vector<N, T>& v) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++) {
        temp[i] = std::abs(v[i]);
    }
    return temp;
}

//向量点乘
template<size_t N, typename T>
T Dot(const Vector<N, T>& v1, const Vector<N, T>& v2) {
    T temp = 0;
    for (size_t i = 0; i < N; i++) {
        temp += v1[i] * v2[i];
    }
    return temp;
}

//向量的模
template<size_t N, typename T>
inline T LengthSqrt(const Vector<N, T>& v) {
    T sum = 0;
    for (int i = 0; i < N; i++) {
        sum += v[i] * v[i];
    }
    return sum;
}

template<size_t N, typename T>
inline T Length(const Vector<N, T>& v) {
    return std::sqrt(LengthSqrt(v));
}

//向量归一化
template<size_t N, typename T>
inline Vector<N, T> Normalize(const Vector<N, T>& v) {
    return v / Length(v);
}

template<size_t N, typename T>
inline Vector<N, T>& Normalized(Vector<N, T>& v) {
    v /= Length(v);
    return v;
}

//二维矢量叉乘
template<typename T>
inline T Cross(const Vector<2, T>& v1, const Vector<2, T>& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

//三维矢量叉乘
template<typename T>
inline Vector<3, T> Cross(const Vector<3, T>& v1, const Vector<3, T>& v2) {
    return {v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v2.z * v1.x, v1.x * v2.y - v2.x * v1.y};
}

//最小维度的值
template<size_t N, typename T>
inline T MinComponent(const Vector<N, T>& v) {
    T min = std::numeric_limits<T>::max();
    for (size_t i = 0; i < N; i++) {
        min = std::min(min, v[i]);
    }
    return min;
}

//最大维度的值
template<size_t N, typename T>
inline T MaxComponent(const Vector<N, T>& v) {
    T max = std::numeric_limits<T>::lowest();
    for (size_t i = 0; i < N; i++) {
        max = std::max(max, v[i]);
    }
    return max;
}

//两向量取各维度最小值组成新的向量
template<size_t N, typename T>
inline Vector<N, T> Min(const Vector<N, T>& v1, const Vector<N, T>& v2) {
    Vector<N, T> min;
    for (size_t i = 0; i < N; i++) {
        min[i] = std::min(v1[i], v2[i]);
    }
    return min;
}

//两向量取各维度最大值组成新的向量
template<size_t N, typename T>
inline Vector<N, T> Max(const Vector<N, T>& v1, const Vector<N, T>& v2) {
    Vector<N, T> max;
    for (size_t i = 0; i < N; i++) {
        max[i] = std::max(v1[i], v2[i]);
    }
    return max;
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