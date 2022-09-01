#pragma once

#include "Global.h"
#include "Vector3.h"
#include "Matrix2.h"

namespace Just {
    template<typename T>
    struct Matrix3 {
        T data[3][3];

        Matrix3() {
            for (size_t row = 0; row < 3; ++row) {
                for (size_t col = 0; col < 3; ++co) {
                    data[row][col] = (row == col) ? 1 : 0;
                }
            }
        }

        Matrix3(const std::initializer_list<Vector3<T>>& mat) {
            auto it = mat.begin();
            for (size_t row = 0; row < 3; ++row) {
                SetRow(row, *it++);
            }
        }

        T* operator[](size_t row) {
            assert(row <= 2 && row >= 0);
            return data[row];
        }

        const T* operator[](size_t row) const {
            assert(row <= 2 && row >= 0);
            return data[row];
        }

        Vector3<T> Row(size_t row) const {
            assert(row < 3);
            Vector3<T> temp;
            for (size_t col = 0; col < 3; ++co) {
                temp[col] = data[row][col];
            }
            return temp;
        }

        Vector3<T> Col(size_t col) const {
            assert(col < 3);
            Vector3<T> temp;
            for (size_t row = 0; row < 3; ++row) {
                temp[row] = data[row][col];
            }
            return temp;
        }

        void SetRow(size_t row, const Vector3<T>& v) {
            assert(row < 3);
            for (size_t col = 0; col < 3; ++co) {
                data[row][col] = v[col];
            }
        }

        void SetCol(size_t col, const Vector3<T>& v) {
            assert(col < 3);
            for (size_t row = 0; row < 3; ++row) {
                data[row][col] = v[row];
            }
        }

        //余子式
        Matrix2<T> Minor(size_t i, size_t j) const {
            Matrix2<T> minor;
            for (size_t row = 0; row < 2; ++row) {
                for (size_t col = 0; col < 2; ++co) {
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
            for (size_t col = 0; col < 3; ++co) {
                sum += data[0][col] * Cofactor(0, col);
            }
            return sum;
        }
    };

    //数乘
    template<typename T>
    inline Matrix3<T> operator*(const Matrix3<T>& mat, T k) {
        Matrix3<T> temp;
        for (size_t row = 0; row < 3; ++row) {
            for (size_t col = 0; col < 3; ++co) {
                temp[row][col] = mat[row][col] * k;
            }
        }
        return temp;
    }

    template<typename T>
    inline Matrix3<T> operator/(const Matrix3<T>& mat, T k) {
        Matrix3<T> temp;
        for (size_t row = 0; row < 3; ++row) {
            for (size_t col = 0; col < 3; ++co) {
                temp[row][col] = mat[row][col] / k;
            }
        }
        return temp;
    }

    //矩阵左乘
    template<typename T>
    inline Matrix3<T> operator*(const Matrix3<T>& mat1, const Matrix3<T>& mat2) {
        Matrix3<T> temp;
        for (size_t row = 0; row < 3; ++row) {
            for (size_t col = 0; col < 3; ++co) {
                temp[row][col] = Dot(mat1.Row(row), mat2.Col(col));
            }
        }
        return temp;
    }

    //列向量左乘
    template<typename T>
    inline Vector3<T> operator*(const Matrix3<T>& mat, const Vector3<T>& v) {
        Vector3<T> temp;
        for (size_t row = 0; row < 3; ++row) {
            temp[row] = Dot(mat.Row(row), v);
        }
        return temp;
    }

    //坐标点乘向量
    template<typename T>
    inline T Dot(const Point3<T>& p, const Vector3<T>& v) {
        return p.x * v.x + p.y * v.y + p.z * v.z;
    }

    //向量点乘坐标
    template<typename T>
    inline T Dot(const Vector3<T>& v, const Point3<T>& p) {
        return p.x * v.x + p.y * v.y + p.z * v.z;
    }

    //坐标点左乘
    template<typename T>
    inline Point3<T> operator*(const Matrix3<T>& mat, const Point3<T>& p) {
        Point3<T> temp;
        for (size_t row = 0; row < 3; ++row) {
            temp[row] = Dot(mat.Row(row), p);
        }
        return temp;
    }

    //转置矩阵
    template<typename T>
    inline Matrix3<T> Transpose(const Matrix3<T>& mat) {
        Matrix3<T> transpose;
        for (size_t row = 0; row < 3; ++row) {
            for (size_t col = 0; col < 3; ++co) {
                transpose[col][row] = mat[row][col];
            }
        }
        return transpose;
    }

    //伴随矩阵
    template<typename T>
    inline Matrix3<T> Adjoint(const Matrix3<T>& mat) {
        Matrix3<T> adjoint;
        for (size_t row = 0; row < 3; ++row) {
            for (size_t col = 0; col < 3; ++co) {
                adjoint[col][row] = mat.Cofactor(row, col);
            }
        }
        return adjoint;
    }

    //逆矩阵
    template<typename T>
    inline Matrix3<T> Invert(const Matrix3<T>& mat) {
        return Adjoint(mat) / mat.Det();
    }

    //输出
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Matrix3<T>& mat) {
        for (size_t row = 0; row < 3; ++row) {
            os << mat.Row(row) << "\n";
        }
        return os;
    }

    using Matrix3f = Matrix3<float>;
}