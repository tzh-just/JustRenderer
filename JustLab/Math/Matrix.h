//================================================
// 矩阵模板
//================================================

#pragma once

#include "../Global.h"
#include "Vector.h"

namespace Just {
    template<int ROW, int COL, typename T>
    struct Matrix {
        T data[ROW][COL];

        Matrix() {
            for (int row = 0; row < ROW; row++)
                for (int col = 0; col < COL; col++)
                    data[row][col] = 0;
        }

        Matrix(const std::initializer_list<Vector<COL, T>> &mat) {
            auto it = mat.begin();
            for (int row = 0; row < ROW; row++)
                SetRow(row, *it++);
        }

        Matrix(const Matrix<ROW, COL, T> &other) = default;

        Matrix &operator=(const Matrix<ROW, COL, T> &other) = default;

        T *operator[](int row) {
            assert(row < ROW);
            return data[row];
        }

        const T *operator[](int row) const {
            assert(row < ROW);
            return data[row];
        }

        Vector<COL, T> Row(int row) const {
            assert(row < ROW);
            Vector<COL, T> tmp;
            for (int col = 0; col < COL; col++)
                tmp[col] = data[row][col];
            return tmp;
        }

        Vector<ROW, T> Col(int col) const {
            assert(col < COL);
            Vector<ROW, T> tmp;
            for (int row = 0; row < ROW; row++)
                tmp[row] = data[row][col];
            return tmp;
        }

        void SetRow(int row, const Vector<COL, T> &v) {
            assert(row < ROW);
            for (int col = 0; col < COL; col++)
                data[row][col] = v[col];
        }

        void SetCol(int col, const Vector<ROW, T> &v) {
            assert(col < COL);
            for (int row = 0; row < ROW; row++)
                data[row][col] = v[row];
        }
    };

    using Matrix4f = Matrix<4, 4, float>;
    using Matrix3f = Matrix<3, 3, float>;
}