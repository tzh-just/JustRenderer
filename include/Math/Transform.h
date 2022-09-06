#pragma once

#include "Global.h"
#include "Vector.h"
#include "Matrix.h"

namespace Just {

struct Transform {
    Matrix4f matrix;
    Matrix4f inverse;

    Transform() : matrix(Matrix4f::Identity()), inverse(Matrix4f::Identity()) {}

    explicit Transform(const Matrix4f& matrix)
            : matrix(matrix), inverse(Invert(matrix)) {}

    Transform(const Matrix4f& matrix, const Matrix4f& inverse)
            : matrix(matrix), inverse(inverse) {}
};

//线性变换
inline Transform operator*(const Transform& t1, const Transform& t2) {
    return {t1.matrix * t2.matrix, t2.inverse * t1.inverse};
}

//一对一变换
inline Vector3f operator*(const Transform& trans, const Vector3f& v) {

}

//变换的逆
inline Transform Invert(const Transform& t) {
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
    Matrix4f mat = {
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
    Matrix4f mat = {
            {cosTheta,  0, sinTheta, 0},
            {0,         1, 0,        0},
            {-sinTheta, 0, cosTheta, 0},
            {0,         0, 0,        1}
    };

    return {mat, Transpose(mat)};
}

inline Transform RotateZ(float theta) {
    float sinTheta = std::sin(Radians(theta));
    float cosTheta = std::cos(Radians(theta));
    Matrix4f mat = {
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
    Matrix4f mat = {
            {x, 0, 0, 0},
            {0, y, 0, 0},
            {0, 0, z, 0},
            {0, 0, 0, 1}
    };
    Matrix4f inv = {
            {
                    {1 / x, 0, 0, 0},
                    {0, 1 / y, 0, 0},
                    {0, 0, 1 / z, 0},
                    {0, 0, 0, 1}
            }
    };
    return {mat, inv};
}

inline Transform Translate(const Point3f& delta) {
    Matrix4f mat = {
            {1, 0, 0, delta.x},
            {0, 1, 0, delta.y},
            {0, 0, 1, delta.z},
            {0, 0, 0, 1}
    };
    Matrix4f inv = {
            {1, 0, 0, -delta.x},
            {0, 1, 0, -delta.y},
            {0, 0, 1, -delta.z},
            {0, 0, 0, 1}
    };
    return {mat, inv};
}

inline Transform LookAt(const Point3f& origin, const Point3f& target, const Vector3f& worldUp) {
    Vector3f dir = Normalize(target - origin);
    Vector3f right = Normalize(Cross(Normalize(worldUp), dir));
    Vector3f up = Cross(right, dir);
    Matrix4f mat = {
            {right.x, up.x, dir.x, origin.x},
            {right.y, up.y, dir.y, origin.y},
            {right.z, up.z, dir.z, origin.z},
            {0,       0,    0,     1}
    };
    return {Invert(mat), mat};
}

//正交投影变换
inline Transform Orthographic(float aspectRatio, float fov, float n, float f) {
    return Scale(1, 1, 1 / (f - n)) * Translate(Vector3f(0, 0, -n));
}

//透视投影变换
inline Transform Perspective(float aspectRatio, float fov, float n, float f) {
    //右手系
    Matrix4f persp = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, f / (f - n), -f * n / (f - n),
            0, 0, 1, 0
    };
    //参数far和near为远近平面的长度，即正值
    float invTanHalfFov = 1 / std::tan(Radians(fov / 2));
    return Scale(invTanHalfFov, invTanHalfFov, 1) * Transform(persp);
}

//视口变换
inline Transform ScreenMapping(const Point2f& size) {
    return Transform({
                             {size.x / 2, 0,          0, size.x / 2},
                             {0,          size.y / 2, 0, size.y / 2},
                             {0,          0,          1, 0},
                             {0,          0,          0, 1}
                     });
}
}