#pragma once

#include "Global.h"
#include "Vector.h"

namespace Just {
template<size_t N, typename T>
struct Matrix {
    T data[N][N];

    Matrix() = default;

    Matrix(const Matrix<N, T>& mat) {
        for (size_t row = 0; row < N; row++) {
            for (size_t col = 0; col < N; col++) {
                data[row][col] = mat.data[row][col];
            }
        }
    }

    Matrix(const std::initializer_list<Vector<N, T>>& list) {
        auto it = list.begin();
        for (size_t i = 0; i < N; i++) {
            SetRow(i, *it++);
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

    void SetRow(size_t row, const Vector<N, T>& v) {
        assert(row < N);
        for (size_t i = 0; i < N; i++) {
            data[row][i] = v[i];
        }
    }

    void SetCol(size_t col, const Vector<N, T>& v) {
        assert(col < N);
        for (size_t i = 0; i < N; i++) {
            data[i][col] = v[i];
        }
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


    static Matrix<N, T> Identity() {
        Matrix < N, T > identity;
        for (size_t row = 0; row < N; row++) {
            for (size_t col = 0; col < N; col++) {
                identity[row][col] = row == col ? 1 : 0;
            }
        }
        return identity;
    }
};

//余子式
template<size_t N, typename T>
inline Matrix<N - 1, T> Minor(const Matrix<N, T>& mat, size_t i, size_t j) {
    Matrix < N - 1, T > minor;
    for (size_t row = 0; row < N - 1; row++) {
        for (size_t col = 0; col < N - 1; col++) {
            minor[row][col] = mat.data[row < i ? row : row + 1][col < j ? col : col + 1];
        }
    }
    return minor;
}

//代数余子式
template<size_t N, typename T>
inline T Cofactor(const Matrix<N, T>& mat, size_t row, size_t col) {
    return Det(Minor(mat, row, col)) * ((row + col) % 2 ? -1 : 1);
}

//一阶代数余子式
template<typename T>
inline T Cofactor(const Matrix<1, T>& mat, size_t row, size_t col) {
    return 0;
}

//行列式
template<size_t N, typename T>
inline T Det(const Matrix<N, T>& mat) {
    T sum = 0;
    for (size_t col = 0; col < N; ++col) {
        sum += mat.data[0][col] * Cofactor(mat, 0, col);
    }
    return sum;
}

//一阶行列式
template<typename T>
inline T Det(const Matrix<1, T>& mat) {
    return mat.data[0][0];
}

//二阶行列式
template<typename T>
inline T Det(const Matrix<2, T>& mat) {
    return mat.data[0][0] * mat.data[1][1] - mat.data[0][1] * mat.data[1][0];;
}


//转置矩阵
template<size_t N, typename T>
inline Matrix<N, T> Transpose(const Matrix<N, T>& mat) {
    Matrix < N, T > transpose;
    for (size_t row = 0; row < N; ++row) {
        for (size_t col = 0; col < N; ++col) {
            transpose[col][row] = mat.data[row][col];
        }
    }
    return transpose;
}

//伴随矩阵
template<size_t N, typename T>
inline Matrix<N, T> Adjoint(const Matrix<N, T>& mat) {
    Matrix < N, T > adjoint;
    for (size_t row = 0; row < N; ++row) {
        for (size_t col = 0; col < N; ++col) {
            adjoint[col][row] = Cofactor(mat, row, col);
        }
    }
    return adjoint;
}

//逆矩阵
template<size_t N, typename T>
inline Matrix<N, T> Invert(const Matrix<N, T>& mat) {
    return Adjoint(mat) / Det(mat);
}

//M=A*k
template<size_t N, typename T, typename U>
inline Matrix<N, T> operator*(const Matrix<N, T>& A, U k) {
    Matrix < N, T > temp;
    for (size_t row = 0; row < N; row++) {
        for (size_t col = 0; col < N; col++) {
            temp[row][col] = A[row][col] * k;
        }
    }
    return temp;
}

//M=k*A
template<size_t N, typename T>
inline Matrix<N, T> operator*(T k, const Matrix<N, T>& A) {
    return A * k;
}

//M=A/k
template<size_t N, typename T, typename U>
inline Matrix<N, T> operator/(const Matrix<N, T>& A, U k) {
    return A * (1.0f / k);
}

//M=A*B
template<size_t N, typename T>
inline Matrix<N, T> operator*(const Matrix<N, T>& A, const Matrix<N, T>& B) {
    Matrix < N, T > temp;
    for (size_t row = 0; row < N; row++) {
        for (size_t col = 0; col < N; col++) {
            temp[row][col] = Dot(A.Row(row), B.Col(col));
        }
    }
    return temp;
}

//M=A*v
template<size_t N, typename T>
inline Vector<N, T> operator*(const Matrix<N, T>& A, const Vector<N, T>& v) {
    Vector<N, T> temp;
    for (size_t row = 0; row < N; row++) {
        temp[row] = Dot(v, A.Row(row));
    }
    return temp;
}

template<size_t N, typename T>
inline std::ostream& operator<<(std::ostream& os, const Matrix<N, T>& A) {
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