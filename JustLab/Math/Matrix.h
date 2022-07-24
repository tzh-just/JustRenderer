//================================================
// 矩阵模板
//================================================

#pragma once

#include "../Global.h"
#include "Vector.h"

namespace Just {
    template<uint32_t ROW, uint32_t COL, typename T>
    struct Matrix {
        T data[ROW][COL];

        Matrix() {
            for (uint32_t row = 0; row < ROW; row++)
                for (uint32_t col = 0; col < COL; col++)
                    data[row][col] = 0;
        }

        Matrix(const std::initializer_list<Vector<COL, T>> &mat) {
            auto it = mat.begin();
            for (uint32_t row = 0; row < ROW; row++)
                SetRow(row, *it++);
        }

        Matrix(const Matrix<ROW, COL, T> &other) = default;

        Matrix &operator=(const Matrix<ROW, COL, T> &other) = default;

        T *operator[](uint32_t row) {
            assert(row < ROW);
            return data[row];
        }

        const T *operator[](uint32_t row) const {
            assert(row < ROW);
            return data[row];
        }

        Vector<COL, T> Row(uint32_t row) const {
            assert(row < ROW);
            Vector<COL, T> tmp;
            for (uint32_t col = 0; col < COL; col++)
                tmp[col] = data[row][col];
            return tmp;
        }

        Vector<ROW, T> Col(uint32_t col) const {
            assert(col < COL);
            Vector<ROW, T> tmp;
            for (uint32_t row = 0; row < ROW; row++)
                tmp[row] = data[row][col];
            return tmp;
        }

        void SetRow(uint32_t row, const Vector<COL, T> &v) {
            assert(row < ROW);
            for (uint32_t col = 0; col < COL; col++)
                data[row][col] = v[col];
        }

        void SetCol(uint32_t col, const Vector<ROW, T> &v) {
            assert(col < COL);
            for (uint32_t row = 0; row < ROW; row++)
                data[row][col] = v[row];
        }
    };

    using Matrix4f = Matrix<4, 4, float>;
    using Matrix3f = Matrix<3, 3, float>;
}