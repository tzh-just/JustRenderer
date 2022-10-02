#pragma once

#include "Global.h"
#include "Vector3.h"
#include "Point3.h"

namespace Just {
//ref: pbrt-v3
struct Matrix4x4 {
    //矩阵元素
    float data[4][4];

    //构造函数默认为单位矩阵
    Matrix4x4() {
        for (auto& row: data) {
            for (float& col: row) {
                col = 0.0f;
            }
        }
    }

    explicit Matrix4x4(float mat[4][4]) {
        memcpy(data, mat, 16 * sizeof(float));
    }

    Matrix4x4(float t00, float t01, float t02, float t03,
              float t10, float t11, float t12, float t13,
              float t20, float t21, float t22, float t23,
              float t30, float t31, float t32, float t33) {
        data[0][0] = t00;
        data[0][1] = t01;
        data[0][2] = t02;
        data[0][3] = t03;
        data[1][0] = t10;
        data[1][1] = t11;
        data[1][2] = t12;
        data[1][3] = t13;
        data[2][0] = t20;
        data[2][1] = t21;
        data[2][2] = t22;
        data[2][3] = t23;
        data[3][0] = t30;
        data[3][1] = t31;
        data[3][2] = t32;
        data[3][3] = t33;
    }

    //拷贝构造函数
    Matrix4x4(const Matrix4x4& mat) {
        memcpy(data, mat.data, 16 * sizeof(float));
    }

    //索引
    float* operator[](size_t index) {
        assert(index < 4);
        return data[index];
    }

    const float* operator[](size_t index) const {
        assert(index < 4);
        return data[index];
    }


    static Matrix4x4 Identity() {
        return {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        };
    }
};

//矩阵数乘
template<typename T>
Matrix4x4 operator*(const Matrix4x4& mat, T t) {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = mat[i][j] * t;
        }
    }
    return result;
}

template<typename T>
Matrix4x4 operator*(T t, const Matrix4x4& mat) {
    return mat * t;
}

//矩阵数除
template<typename T>
Matrix4x4 operator/(const Matrix4x4& mat, T k) {
    assert(k != 0.0f);
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = mat[i][j] / k;
        }
    }
    return result;
}

//矩阵乘法
Matrix4x4 operator*(const Matrix4x4& mat1, const Matrix4x4& mat2) {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return result;
}

//转置矩阵
inline Matrix4x4 Transpose(const Matrix4x4& mat) {
    return {
            mat[0][0], mat[1][0], mat[2][0], mat[3][0],
            mat[0][1], mat[1][1], mat[2][1], mat[3][1],
            mat[0][2], mat[1][2], mat[2][2], mat[3][2],
            mat[0][3], mat[1][3], mat[2][3], mat[3][3]
    };
}

//伴随矩阵
inline Matrix4x4 Adjoint(const Matrix4x4& mat) {
    Matrix4x4 adjoint;
    //4x4遍历
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            //3x3余子式
            float minor3x3[3][3];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (i != row && j != col) {
                        minor3x3[i > row ? i - 1 : i][j > col ? j - 1 : j] = mat[i][j];
                    }
                }
            }
            //余子式行列式
            for (int i = 0; i < 3; ++i) {
                if (minor3x3[0][i] != 0.0f) {
                    float det = minor3x3[1][(i + 1) % 3] * minor3x3[2][(i + 2) % 3] -
                                minor3x3[1][(i + 2) % 3] * minor3x3[2][(i + 1) % 3];
                    adjoint[col][row] += minor3x3[0][i] * det;
                }
            }
            adjoint[col][row] *= (row + col) % 2 == 0 ? 1.0f : -1.0f;
        }
    }
    return adjoint;
}

//逆矩阵
inline Matrix4x4 Inverse(const Matrix4x4& mat) {
    Matrix4x4 adjoint = Adjoint(mat);
    float det = 0.0f;
    for (int i = 0; i < 4; ++i) {
        det += mat[0][i] * adjoint[i][0];
    }
    return adjoint / det;
}

}