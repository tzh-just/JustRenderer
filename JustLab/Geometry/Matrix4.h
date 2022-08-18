//================================================
// 四阶矩阵
//================================================

#pragma once

#include "Global.h"
#include "Vector3.h"
#include "Point3.h"
#include "Homogeneous.h"
#include "Matrix3.h"

namespace Just {
    template<typename T>
    struct Matrix4 {
        T data[4][4];

        Matrix4() {
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    data[row][col] = (row == col) ? 1 : 0;
                }
            }
        }

        Matrix4(const std::initializer_list<Homogeneous<T>>& mat) {
            assert(mat.size() == 4);
            auto it = mat.begin();
            for (int row = 0; row < 4; row++) {
                SetRow(row, *it++);
            }
        }

        T* operator[](int row) {
            assert(row <= 3 && row >= 0);
            return data[row];
        }

        const T* operator[](int row) const {
            assert(row <= 3 && row >= 0);
            return data[row];
        }

        //获取指定行向量
        Homogeneous<T> Row(int row) const {
            assert(row <= 3 && row >= 0);
            return Homogeneous<T>(data[row][0], data[row][1], data[row][2], data[row][3]);
        }

        //获取指定列向量
        Homogeneous<T> Col(int col) const {
            assert(col <= 3 && col >= 0);
            return Homogeneous<T>(data[0][col], data[1][col], data[2][col], data[3][col]);
        }

        //设置指定行向量
        void SetRow(size_t row, const Homogeneous<T>& h) {
            assert(row <= 3 && row >= 0);
            for (size_t col = 0; col < 4; col++) {
                data[row][col] = h[col];
            }
        }

        //设置指定列向量
        void SetCol(size_t col, const Homogeneous<T>& h) {
            assert(col <= 3 && col >= 0);
            for (size_t row = 0; row < 4; row++) {
                data[row][col] = h[row];
            }
        }

        //余子式
        Matrix3<T> Minor(int i, int j) const {
            Matrix3<T> minor;
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    minor[row][col] = data[row < i ? row : row + 1][col < j ? col : col + 1];
                }
            }
            return minor;
        }

        //代数余子式
        float Cofactor(int row, int col) const {
            return Minor(row, col).Det() * ((row + col) % 2 ? -1 : 1);
        }

        //行列式
        float Det() const {
            T sum = 0;
            for (int col = 0; col < 4; col++) {
                sum += data[0][col] * Cofactor(0, col);
            }
            return sum;
        }
    };

    //数乘
    template<typename T>
    inline Matrix4<T> operator*(const Matrix4<T>& mat, T k) const {
        Matrix4<T> temp;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                temp[row][col] = mat[row][col] * k;
            }
        }
        return temp;
    }

    template<typename T>
    inline Matrix4<T> operator/(const Matrix4<T>& mat, T k) const {
        Matrix4<T> temp;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                temp[row][col] = mat[row][col] / k;
            }
        }
        return temp;
    }

    //矩阵左乘
    template<typename T>
    inline Matrix4<T> operator*(const Matrix4<T>& mat1, const Matrix4<T>& mat2) const {
        Matrix4<T> temp;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                temp[row][col] = Dot(mat1[row], mat2.[col]);
            }
        }
        return temp;
    }

    //点乘
    template<typename T>
    inline T Dot(const Homogeneous<T>& h1, const Homogeneous<T>& h2) {
        return h1.x * h2.x + h1.y * h2.y + h1.z * h2.z + h1.w * h2.w;
    }

    template<typename T>
    inline T Dot(const Homogeneous<T>& h, const Vector3<T>& v) {
        return h.x * v.x + h.y * v.y + h.z * v.z + h.w * 0;
    }

    template<typename T>
    inline T Dot(const Homogeneous<T>& h, const Point3<T>& p) {
        return h.x * p.x + h.y * p.y + h.z * p.z + h.w * 1;
    }

    //列向量左乘
    template<typename T>
    inline Vector3<T> operator*(const Matrix4<T>& mat, const Vector3<T>& v) const {
        Vector3<T> temp;
        for (int row = 0; row < 4; row++) {
            temp[row] = Dot(mat.Row(row), v);
        }
        return temp;
    }

    //坐标点左乘
    template<typename T>
    inline Point3 <T> operator*(const Matrix4<T>& mat, const Point3 <T>& p) const {
        Point3 <T> temp;
        for (int row = 0; row < 4; row++) {
            temp[row] = Dot(mat.Row(row), p);
        }
        return temp;
    }

    //转置矩阵
    template<typename T>
    inline Matrix4<T> Transpose(const Matrix4<T>& mat) {
        Matrix4<T> transpose;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                transpose[col][row] = mat[row][col];
            }
        }
        return transpose;
    };

    //伴随矩阵
    template<typename T>
    inline Matrix4<T> Adjoint(const Matrix4<T>& mat) {
        Matrix4<T> adjoint;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
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
        for (int row = 0; row < 4; row++) {
            os << mat.[row] << "\n";
        }
        return os;
    }

    using Matrix4f = Matrix4<float>;
}