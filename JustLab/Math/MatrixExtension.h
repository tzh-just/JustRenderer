#pragma once

#include "Matrix.h"

namespace Just{
    //输出
    template<size_t ROW, size_t COL, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Matrix<ROW, COL, T> &mat) {
        for(auto& row : mat){
            os << "{"  << row << "}";
        }
        return os;
    }

    //加法
    template<size_t ROW, size_t COL, typename T>
    inline Matrix<ROW, COL, T> operator+(const Matrix<ROW, COL, T> &mat1, const Matrix<ROW, COL, T> &mat2) {
        Matrix<ROW, COL, T> tmp;
        for (size_t row = 0; row < ROW; row++)
            for (size_t col = 0; col < COL; col++)
                tmp[row][col] = mat1[row][col] + mat2[row][col];
        return tmp;
    }

    //减法
    template<size_t ROW, size_t COL, typename T>
    inline Matrix<ROW, COL, T> operator-(const Matrix<ROW, COL, T> &mat1, const Matrix<ROW, COL, T> &mat2) {
        Matrix<ROW, COL, T> tmp;
        for (size_t row = 0; row < ROW; row++)
            for (size_t col = 0; col < COL; col++)
                tmp[row][col] = mat1[row][col] - mat2[row][col];
        return tmp;
    }

    //矩阵左乘
    template<size_t ROW, size_t COM, size_t COL, typename T>
    inline Matrix<ROW, COL, T> operator*(const Matrix<ROW, COM, T> &mat1, const Matrix<COM, COL, T> &mat2) {
        Matrix<ROW, COL, T> tmp;
        for (size_t row = 0; row < ROW; row++)
            for (size_t col = 0; col < COL; col++)
                tmp[row][col] = Dot(mat1.Row(row), mat2.Col(col));
        return tmp;
    }

    //列向量左乘
    template<size_t ROW, size_t COL, typename T>
    inline Vector<ROW, T> operator*(const Matrix<ROW, COL, T> &mat, const Vector<COL, T> &v1) {
        Vector<ROW, T> v2;
        for (size_t row = 0; row < ROW; row++)
            v2[row] = Dot(v1, mat.Row(row));
        return v2;
    }

    //行向量右乘
    template<size_t ROW, size_t COL, typename T>
    inline Vector<COL, T> operator*(const Vector<ROW, T> &v1, const Matrix<ROW, COL, T> &mat) {
        Vector<COL, T> v2;
        for (size_t col = 0; col < COL; col++)
            v2[col] = Dot(v1, mat.Col(col));
        return v2;
    }

    //数乘
    template<size_t ROW, size_t COL, typename T>
    inline Matrix<ROW, COL, T> operator*(const Matrix<ROW, COL, T> &mat, T k) {
        Matrix<ROW, COL, T> tmp;
        for (size_t row = 0; row < ROW; row++)
            for (size_t col = 0; col < COL; col++)
                tmp[row][col] = mat[row][col] * k;
        return tmp;
    }

    template<size_t ROW, size_t COL, typename T>
    inline Matrix<ROW, COL, T> operator*(T k, const Matrix<ROW, COL, T> &mat) {
        Matrix<ROW, COL, T> tmp;
        for (size_t row = 0; row < ROW; row++)
            for (size_t col = 0; col < COL; col++)
                tmp[row][col] = mat[row][col] * k;
        return tmp;
    }

    template<size_t ROW, size_t COL, typename T>
    inline Matrix<ROW, COL, T> operator/(const Matrix<ROW, COL, T> &mat, T k) {
        Matrix<ROW, COL, T> tmp;
        for (size_t row = 0; row < ROW; row++)
            for (size_t col = 0; col < COL; col++)
                tmp[row][col] = mat[row][col] / k;
        return tmp;
    }

    //特化一阶行列式
    template<typename T>
    inline T Det(const Matrix<1, 1, T> &mat) {
        return mat[0][0];
    }

    //特化二阶方阵行列式
    template<typename T>
    inline T Det(const Matrix<2, 2, T> &mat) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }

    //多阶行列式
    template<size_t N, typename T>
    inline T Det(const Matrix<N, N, T> &mat) {
        T sum = 0;
        for (size_t col = 0; col < N; col++)
            sum += mat[0][col] * Cofactor(mat, 0, col);
        return sum;
    }

    //余子式
    template<size_t ROW, size_t COL, typename T>
    inline Matrix<ROW - 1, COL - 1, T> Minor(const Matrix<ROW, COL, T> &mat, size_t i, size_t j) {
        Matrix<ROW - 1, COL - 1, T> minor;
        for (size_t row = 0; row < ROW - 1; row++)
            for (size_t col = 0; col < COL - 1; col++)
                minor[row][col] = mat[row < i ? row : row + 1][col < j ? col : col + 1];
        return minor;
    }

    //代数余子式
    template<size_t N, typename T>
    inline T Cofactor(const Matrix<N, N, T> &mat, size_t row, size_t col) {
        return Det(Minor(mat, row, col)) * ((row + col) % 2 ? -1 : 1);
    }

    //转置矩阵
    template<size_t ROW, size_t COL, typename T>
    inline Matrix<COL, ROW, T> Transpose(const Matrix<ROW, COL, T> &mat) {
        Matrix<COL, ROW, T> transpose;
        for (size_t row = 0; row < ROW; row++)
            for (size_t col = 0; col < COL; col++)
                transpose[col][row] = mat[row][col];
        return transpose;
    };

    //伴随矩阵：元素下标对应代数余子式组成的矩阵的转置
    template<size_t N, typename T>
    inline Matrix<N, N, T> Adjoint(const Matrix<N, N, T> &mat) {
        Matrix<N, N, T> adjoint;
        for (size_t row = 0; row < N; row++)
            for (size_t col = 0; col < N; col++)
                adjoint[col][row] = Cofactor(mat, row, col);
        return adjoint;
    }

    //逆矩阵
    template<size_t N, typename T>
    inline Matrix<N, N, T> Invert(const Matrix<N, N, T> &mat) {
        return Adjoint(mat) / Det(mat);
    }
}