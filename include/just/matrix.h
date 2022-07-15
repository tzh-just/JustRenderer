#pragma once

#include "definition.h"
#include "vector.h"

namespace Just {
    template<size_t ROW, size_t COL, typename T>
    struct Matrix {
        T data[ROW][COL];

        Matrix() {
            for (size_t row = 0; row < ROW; row++) {
                for (size_t col = 0; col < COL; col++) {
                    data[row][col] = T();
                }
            }
        }

        Matrix(const std::initializer_list<Vector<COL, T>> &mat) {
            auto it = mat.begin();
            for (size_t row = 0; row < ROW; row++)
                SetRow(row, *it++);
        }

        Matrix(const Matrix<ROW, COL, T> &other) = default;

        Matrix &operator=(const Matrix<ROW, COL, T> &other) = default;

        T *operator[](size_t row) {
            assert(row < ROW);
            return data[row];
        }

        const T *operator[](size_t row) const {
            assert(row < ROW);
            return data[row];
        }

        Vector<COL, T> Row(size_t row) const {
            assert(row < ROW);
            Vector<COL, T> tmp;
            for (size_t col = 0; col < COL; col++)
                tmp[col] = data[row][col];
            return tmp;
        }

        Vector<ROW, T> Col(size_t col) const {
            assert(col < COL);
            Vector<ROW, T> tmp;
            for (size_t row = 0; row < COL; row++)
                tmp[row] = data[row][col];
            return tmp;
        }

        void SetRow(size_t row, const Vector<COL, T> &v) {
            assert(row < ROW);
            for (size_t col = 0; col < COL; col++)
                data[row][col] = v[col];
        }

        void SetCol(size_t col, const Vector<ROW, T> &v) {
            assert(col < COL);
            for (size_t row = 0; row < ROW; row++)
                data[row][col] = v[row];
        }

        static Matrix Identity() {
            Matrix mat;
            for (size_t row = 0; row < ROW; row++) {
                for (size_t col = 0; col < COL; col++)
                    mat[row][col] = (row == col) ? 1 : 0;
            }
            return mat;
        }

        static Matrix Zero() {
            Matrix mat;
            for (size_t row = 0; row < ROW; row++) {
                for (size_t col = 0; col < COL; col++)
                    mat[row][col] = 0;
            }
            return mat;
        }
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    template<size_t ROW, size_t COL, typename T>
    inline std::ostream &operator<<(std::ostream &os, const Matrix<ROW, COL, T> &v) {
        for (size_t row = 0; row < ROW; row++) {
            os << "[";
            for (size_t col = 0; col < COL; col++) {
                os << v.data[row][col];
                if (col + 1 != COL)
                    os << ",";
            }
            os << "]";
            if (row + 1 != ROW)
                os << std::endl;;
        }
        return os;
    }

    using Matrix4f = Matrix<4, 4, float>;
    using Matrix3f = Matrix<3, 3, float>;
}