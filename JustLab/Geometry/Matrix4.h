//================================================
// 四阶矩阵
//================================================

#pragma once

#include "Global.h"
#include "Vector4.h"
#include "Point4.h"
#include "Matrix3.h"

namespace Just {
    template<typename T>
    struct Matrix4 {
        T data[4][4];

        Matrix4() {
            for (size_t row = 0; row < 4; row++) {
                for (size_t col = 0; col < 4; col++) {
                    data[row][col] = (row == col) ? 1 : 0;
                }
            }
        }

        Matrix4(const std::initializer_list<Vector4<T>>& mat) {
            assert(mat.size() == 4);
            auto it = mat.begin();
            for (size_t row = 0; row < 4; row++) {
                SetRow(row, *it++);
            }
        }

        T* operator[](size_t row) {
            assert(row <= 3 && row >= 0);
            return data[row];
        }

        const T* operator[](size_t row) const {
            assert(row <= 3 && row >= 0);
            return data[row];
        }

        Vector4<T> Row(size_t row) const {
            assert(row < 4);
            Vector4<T> v;
            for (size_t col = 0; col < 4; col++) {
                v[col] = data[row][col];
            }
            return v;
        }

        Vector4<T> Col(size_t col) const {
            assert(col < 4);
            Vector4<T> v;
            for (size_t row = 0; row < 4; row++) {
                v[row] = data[row][col];
            }
            return v;
        }

        //设置指定行向量
        void SetRow(size_t row, const Vector4<T>& h) {
            assert(row <= 3 && row >= 0);
            for (size_t col = 0; col < 4; col++) {
                data[row][col] = h[col];
            }
        }

        //设置指定列向量
        void SetCol(size_t col, const Vector4<T>& h) {
            assert(col <= 3 && col >= 0);
            for (size_t row = 0; row < 4; row++) {
                data[row][col] = h[row];
            }
        }

        //余子式
        Matrix3<T> Minor(size_t i, size_t j) const {
            Matrix3<T> minor;
            for (size_t row = 0; row < 3; row++) {
                for (size_t col = 0; col < 3; col++) {
                    minor[row][col] = data[row < i ? row : row + 1][col < j ? col : col + 1];
                }
            }
            return minor;
        }

        //代数余子式
        T Cofactor(size_t row, size_t col) const {
            return Minor(row, col).Det() * ((row + col) % 2 ? -1 : 1);
        }

        //行列式
        T Det() const {
            T sum = 0;
            for (size_t col = 0; col < 4; col++) {
                sum += data[0][col] * Cofactor(0, col);
            }
            return sum;
        }
    };

    //数乘
    template<typename T>
    inline Matrix4<T> operator*(const Matrix4<T>& mat, T k) {
        Matrix4<T> temp;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                temp[row][col] = mat[row][col] * k;
            }
        }
        return temp;
    }

    template<typename T>
    inline Matrix4<T> operator/(const Matrix4<T>& mat, T k) {
        Matrix4<T> temp;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                temp[row][col] = mat[row][col] / k;
            }
        }
        return temp;
    }

    //矩阵左乘
    template<typename T>
    inline Matrix4<T> operator*(const Matrix4<T>& mat1, const Matrix4<T>& mat2) {
        Matrix4<T> temp;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                temp[row][col] = Dot(mat1.Row(row), mat2.Col(col));
            }
        }
        return temp;
    }

    //列向量左乘
    template<typename T>
    inline Vector4<T> operator*(const Matrix4<T>& mat, const Vector4<T>& v) {
        Vector4<T> temp;
        for (size_t row = 0; row < 4; row++) {
            temp[row] = Dot(mat.Row(row), v);
        }
        return temp;
    }

    //坐标点左乘
    template<typename T>
    inline Point4<T> operator*(const Matrix4<T>& mat, const Point4<T>& p) {
        Point4<T> temp;
        for (size_t row = 0; row < 4; row++) {
            temp[row] = Dot(mat.Row(row), p);
        }
        return temp;
    }

    //转置矩阵
    template<typename T>
    inline Matrix4<T> Transpose(const Matrix4<T>& mat) {
        Matrix4<T> transpose;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                transpose[col][row] = mat[row][col];
            }
        }
        return transpose;
    }

    //伴随矩阵
    template<typename T>
    inline Matrix4<T> Adjoint(const Matrix4<T>& mat) {
        Matrix4<T> adjoint;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                adjoint[col][row] = mat.Cofactor(row, col);
            }
        }
        return adjoint;
    }

    //逆矩阵
    template<typename T>
    inline Matrix4<T> Invert(const Matrix4<T>& mat) {
        return Adjoint(mat) / mat.Det();
    }

    //输出
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const Matrix4<T>& mat) {
        for (size_t row = 0; row < 4; row++) {
            os << mat.Row(row) << "\n";
        }
        return os;
    }

    using Matrix4f = Matrix4<float>;
}