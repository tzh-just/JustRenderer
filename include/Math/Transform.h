#pragma once

#include "Global.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Geometry/Ray.h"
#include "Geometry/Bounds.h"

namespace Just {
//Ref: pbrt-v3
struct Transform {
    Matrix4x4 matrix;
    Matrix4x4 inverse;

    Transform() : matrix(Matrix4x4::Identity()), inverse(Matrix4x4::Identity()) {}

    explicit Transform(const Matrix4x4& matrix)
            : matrix(matrix), inverse(Inverse(matrix)) {}

    Transform(const Matrix4x4& matrix, const Matrix4x4& inverse)
            : matrix(matrix), inverse(inverse) {}


    Ray TransRay(const Ray& ray) const {
        return {TransPoint(ray.origin), TransVector(ray.direction)};
    }

    Ray TransRay(const Point3f& origin, const Vector3f& direction) const {
        return {TransPoint(origin), TransVector(direction)};
    }

    template<typename T>
    Vector3<T> TransVector(const Vector3<T>& v) const {
        Vector3f result;
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                result[row] += matrix[row][col] * v[col];
            }
        }
        return result;
    }

    template<typename T>
    Point3<T> TransPoint(const Point3<T>& point) const {
        T homogenized[4] = {point.x, point.y, point.z, 1};
        T result[4] = {0, 0, 0, 0};
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                result[row] += matrix[row][col] * homogenized[col];
            }
        }
        return Point3f(result[0], result[1], result[2]) / result[3];
    }

    template<typename T>
    Vector3<T> TransNormal(const Vector3<T>& n) const {
        Vector3<T> result;
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                result[row] += inverse[col][row] * n[col];
            }
        }
        return result;
    }

    template<typename T>
    Bounds3<T> operator()(const Bounds3<T>& bounds) const {
        Bounds3<T> result;
        for (int i = 0; i < 8; ++i) {
            result = Union(result, (*this)(bounds[i]));
        }
        return result;
    }
};

//线性变换
inline Transform operator*(const Transform& t1, const Transform& t2) {
    return {t1.matrix * t2.matrix, t2.inverse * t1.inverse};
}

//一对一变换
inline Vector3f operator*(const Transform& t, const Vector3f& v) {
    return {};
    //return t.matrix * v;
}

//变换的逆
inline Transform Inverse(const Transform& t) {
    return {t.inverse, t.matrix};
}

//变换的转置
inline Transform Transpose(const Transform& t) {
    return {Transpose(t.matrix), Transpose(t.inverse)};
}

//旋转变换
inline Transform RotateX(float theta) {
    float sinTheta = std::sin(Radians(theta));
    float cosTheta = std::cos(Radians(theta));
    Matrix4x4 mat = {
            1, 0, 0, 0,
            0, cosTheta, -sinTheta, 0,
            0, sinTheta, cosTheta, 0,
            0, 0, 0, 1
    };
    return {mat, Transpose(mat)};
}

inline Transform RotateY(float theta) {
    float sinTheta = std::sin(Radians(theta));
    float cosTheta = std::cos(Radians(theta));
    Matrix4x4 mat = {
            cosTheta, 0, sinTheta, 0,
            0, 1, 0, 0,
            -sinTheta, 0, cosTheta, 0,
            0, 0, 0, 1
    };

    return {mat, Transpose(mat)};
}

inline Transform RotateZ(float theta) {
    float sinTheta = std::sin(Radians(theta));
    float cosTheta = std::cos(Radians(theta));
    Matrix4x4 mat = {
            cosTheta, -sinTheta, 0, 0,
            sinTheta, cosTheta, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
    return {mat, Transpose(mat)};
}

//旋转变换
inline Transform Rotate(float x, float y, float z) {
    return RotateZ(z) * RotateY(y) * RotateX(x);
}

//缩放变换
inline Transform Scale(float x, float y, float z) {
    Matrix4x4 mat = {
            x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1
    };
    Matrix4x4 inv = {

            1 / x, 0, 0, 0,
            0, 1 / y, 0, 0,
            0, 0, 1 / z, 0,
            0, 0, 0, 1
    };
    return {mat, inv};
}

inline Transform Translate(const Vector3f& delta) {
    Matrix4x4 mat = {
            1, 0, 0, delta.x,
            0, 1, 0, delta.y,
            0, 0, 1, delta.z,
            0, 0, 0, 1
    };
    Matrix4x4 inv = {
            1, 0, 0, -delta.x,
            0, 1, 0, -delta.y,
            0, 0, 1, -delta.z,
            0, 0, 0, 1
    };
    return {mat, inv};
}

inline Transform LookAt(const Point3f& origin, const Point3f& target, const Vector3f& worldUp) {
    Vector3f dir = Normalize(target - origin);
    Vector3f right = Normalize(Cross(Normalize(worldUp), dir));
    Vector3f up = Cross(dir, right);
    Matrix4x4 mat = {
            right.x, up.x, dir.x, origin.x,
            right.y, up.y, dir.y, origin.y,
            right.z, up.z, dir.z, origin.z,
            0, 0, 0, 1
    };
    return {Inverse(mat), mat};
}

//正交投影变换
inline Transform Orthographic(float fov, float n, float f) {
    return Scale(1, 1, 1 / (f - n)) * Translate({0, 0, -n});
}

//透视投影变换
inline Transform Perspective(float fov, float n, float f) {
    //右手系
    float recip = 1.0f / (f - n);
    float cot = 1.0f / std::tan(Radians(fov) / 2.0f);
    Matrix4x4 persp = {
            cot, 0, 0, 0,
            0, cot, 0, 0,
            0, 0, f * recip, -f * n * recip,
            0, 0, 1, 0
    };
    return Transform(persp);
}
}