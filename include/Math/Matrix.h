#pragma once

#include "Global.h"
#include "Vector.h"

namespace Just {
    template<size_t N, typename T>
    struct Matrix {
        T data[N][N];

        Matrix() : data() {}

        Matrix(const std::initializer_list<Vector<N, T>>& mat) {
            auto it = mat.begin();
            for (size_t row = 0; row < N; row++) {
                SetRow(row, *it++);
            }
        }

        T* operator[](size_t i) {
            assert(i < N);
            return data[i];
        }

        const T* operator[](size_t i) const {
            assert(i < N);
            return data[i];
        }

        Vector<N, T> Row(size_t row) const {
            assert(row < N);
            Vector<N, T> temp;
            for (size_t col = 0; col < N; col++) {
                temp[col] = data[row][col];
            }
            return temp;
        }

        Vector<N, T> Col(size_t col) const {
            assert(col < N);
            Vector<N, T> temp;
            for (size_t row = 0; row < N; row++) {
                temp[row] = data[row][col];
            }
            return temp;
        }

        void SetRow(size_t row, const Vector<N, T>& v) {
            assert(row < N);
            for (size_t col = 0; col < N; col++) {
                data[row][col] = v[col];
            }
        }

        void SetCol(size_t col, const Vector<N, T>& v) {
            assert(col < N);
            for (size_t row = 0; row < N; row++) {
                data[row][col] = v[row];
            }
        }

        Matrix<N - 1, T> Minor(size_t i, size_t j) {
            Matrix<N - 1, T> minor;
            for (size_t row = 0; row < N - 1; row++) {
                for (size_t col = 0; col < N - 1; col++) {
                    minor[row][col] = data[row < i ? row : row + 1][col < j ? col : col + 1];
                }
            }
            return minor;
        }

        T Cofactor(size_t row, size_t col) {
            return Minor(row, col).Det() * ((row + col) % 2 ? -1 : 1);
        }

        static T Det(const Matrix<N, T>& mat) {
            T sum = 0;
            for (size_t col = 0; col < N; col++) {
                sum += mat[0][col] * mat.Cofactor(0, col);
            }
            return sum;
        }

        static Matrix Transpose(const Matrix<N, T>& mat) {
            Matrix transpose;
            for (size_t row = 0; row < N; row++) {
                for (size_t col = 0; col < N; col++) {
                    transpose[col][row] = mat[row][col];
                }
            }
            return transpose;
        };

        static Matrix Adjoint(const Matrix<N, T>& mat) {
            Matrix adjoint;
            for (size_t row = 0; row < N; row++) {
                for (size_t col = 0; col < N; col++) {
                    adjoint[col][row] = mat.Cofactor(row, col);
                }
            }
            return adjoint;
        }

        static Matrix Invert(const Matrix<N, T>& mat) {
            return Adjoint(mat) / Det(mat);
        }
    };

    template<typename T>
    struct Matrix<2, T> {
        T data[2][2];

        Matrix() : data() {}

        T* operator[](size_t i) {
            std::cout << "2 = " << 2 << ", i = " << i << " -test \n";
            assert(i < 2);
            return data[i];
        }

        const T* operator[](size_t i) const {
            assert(i < 2);
            return data[i];
        }

        static T Det(const Matrix<2,T>& mat) {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        }
    };

    //M=A*k
    template<size_t N, typename T>
    Matrix<N, T> operator*(const Matrix<N, T>& A, T k) {
        Matrix<N, T> temp;
        for (size_t row = 0; row < N; row++) {
            for (size_t col = 0; col < N; col++) {
                temp[row][col] = A[row][col] * k;
            }
        }
        return temp;
    }

    //M=k*A
    template<size_t N, typename T>
    Matrix<N, T> operator*(T k, const Matrix<N, T>& A) {
        return A * k;
    }

    //M=A/k
    template<size_t N, typename T>
    Matrix<N, T> operator/(const Matrix<N, T>& A, T k) {
        return A * (1 / k);
    }

    //M=A*B
    template<size_t N, typename T>
    Matrix<N, T> operator*(const Matrix<N, T>& A, const Matrix<N, T>& B) {
        Matrix<N, T> temp;
        for (size_t row = 0; row < N; row++) {
            for (size_t col = 0; col < N; col++) {
                temp[row][col] = A.Row(row).Dot(B.Col(col));
            }
        }
        return temp;
    }

    //M=A*v
    template<size_t N, typename T>
    Vector<N, T> operator*(const Matrix<N, T>& A, const Vector<N, T>& v) {
        Vector<N, T> temp;
        for (size_t row = 0; row < N; row++) {
            temp[row] = v.Dot(A.Row(row));
        }
        return temp;
    }

    template<size_t N, typename T>
    std::ostream& operator<<(std::ostream& os, const Matrix<N, T>& A) {
        for (size_t row = 0; row < N; row++) {
            os << "(";
            for (size_t col = 0; col < N; col++) {
                os << A[row][col] << (col < N - 1 ? "," : "");

            }
            os << ")" << "\n";
        }
        return os;
    }

    using Matrix4f = Matrix<4, float>;
    using Matrix3f = Matrix<3, float>;
    using Matrix2f = Matrix<2, float>;
}