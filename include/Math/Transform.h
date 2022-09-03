#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Math.h"

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

inline Transform operator*(const Transform& t1, const Transform& t2) {
    return {t1.matrix * t2.matrix, t2.inverse * t1.inverse};
}

inline Vector3f operator*(const Transform& trans, const Vector3f& v) {
    return Minor(trans.matrix, 3, 3) * v;
}


inline Transform Invert(const Transform& t) {
    return {t.inverse, t.matrix};
}
}