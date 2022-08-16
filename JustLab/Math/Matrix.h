//================================================
// 四阶矩阵
//================================================

#pragma once

#include "Global.h"
#include "Vector.h"

namespace Just
{

    //矩阵模板类
    //-----------------------------------------------------------------------------
    template<size_t N, typename T>
    struct Matrix
    {
        T data[N][N];

        constexpr Matrix() : data() {}

        constexpr Matrix(const std::initializer_list<Vector<N, T>> &A)
        {
            auto it = A.begin();
            for (size_t row = 0; row < N; row++)
            {
                SetRow(row, *it++);
            }
        }

        constexpr T *operator[](size_t i)
        {
            std::cout << "N = " << N << ", i = " << i << " -test \n";
            assert(i < N);
            return data[i];
        }

        constexpr const T *operator[](size_t i) const
        {
            assert(i < N);
            return data[i];
        }

        //获取指定行向量
        constexpr Vector<N, T> Row(size_t row) const
        {
            assert(row < N);
            Vector<N, T> temp;
            for (size_t col = 0; col < N; col++)
            {
                temp[col] = data[row][col];
            }
            return temp;
        }

        //获取指定列向量
        constexpr Vector<N, T> Col(size_t col) const
        {
            assert(col < N);
            Vector<N, T> temp;
            for (size_t row = 0; row < N; row++)
            {
                temp[row] = data[row][col];
            }
            return temp;
        }

        //设置指定行向量
        constexpr void SetRow(size_t row, const Vector<N, T> &v)
        {
            assert(row < N);
            for (size_t col = 0; col < N; col++)
            {
                data[row][col] = v[col];
            }
        }

        //设置指定列向量
        constexpr void SetCol(size_t col, const Vector<N, T> &v)
        {
            assert(col < N);
            for (size_t row = 0; row < N; row++)
            {
                data[row][col] = v[row];
            }
        }

        //余子式
        constexpr Matrix<N - 1, T> Minor(size_t i, size_t j)
        {
            Matrix<N - 1, T> minor;
            for (size_t row = 0; row < N - 1; row++)
            {
                for (size_t col = 0; col < N - 1; col++)
                {
                    minor[row][col] = data[row < i ? row : row + 1][col < j ? col : col + 1];
                }
            }
            return minor;
        }

        //代数余子式
        constexpr T Cofactor(size_t row, size_t col)
        {
            return Minor(row, col).Det() * ((row + col) % 2 ? -1 : 1);
        }

        //行列式
        constexpr T Det()
        {
            T sum = 0;
            for (size_t col = 0; col < N; col++)
            {
                sum += data[0][col] * Cofactor(0, col);
            }
            return sum;
        }

        //转置矩阵
        constexpr Matrix Transpose()
        {
            Matrix transpose;
            for (size_t row = 0; row < N; row++)
            {
                for (size_t col = 0; col < N; col++)
                {
                    transpose[col][row] = data[row][col];
                }
            }
            return transpose;
        };

        //伴随矩阵
        constexpr Matrix Adjoint()
        {
            Matrix adjoint;
            for (size_t row = 0; row < N; row++)
            {
                for (size_t col = 0; col < N; col++)
                {
                    adjoint[col][row] = Cofactor(row, col);
                }
            }
            return adjoint;
        }

        //逆矩阵
        constexpr Matrix Invert()
        {
            return Adjoint() / Det();
        }
    };

    //特化二阶矩阵
    //-----------------------------------------------------------------------------
    template<typename T>
    struct Matrix<2, T>
    {
        T data[2][2];

        constexpr Matrix() : data() {}

        constexpr Matrix(const std::initializer_list<Vector<2, T>> &A)
        {
            auto it = A.begin();
            for (size_t row = 0; row < 2; row++)
            {
                SetRow(row, *it++);
            }
        }

        constexpr T *operator[](size_t i)
        {
            std::cout << "2 = " << 2 << ", i = " << i << " -test \n";
            assert(i < 2);
            return data[i];
        }

        constexpr const T *operator[](size_t i) const
        {
            assert(i < 2);
            return data[i];
        }

        constexpr Vector<2, T> Row(size_t row) const
        {
            assert(row < 2);
            Vector<2, T> temp;
            for (size_t col = 0; col < 2; col++)
            {
                temp[col] = data[row][col];
            }
            return temp;
        }

        constexpr Vector<2, T> Col(size_t col) const
        {
            assert(col < 2);
            Vector<2, T> temp;
            for (size_t row = 0; row < 2; row++)
            {
                temp[row] = data[row][col];
            }
            return temp;
        }

        constexpr void SetRow(size_t row, const Vector<2, T> &v)
        {
            assert(row < 2);
            for (size_t col = 0; col < 2; col++)
            {
                data[row][col] = v[col];
            }
        }

        constexpr void SetCol(size_t col, const Vector<2, T> &v)
        {
            assert(col < 2);
            for (size_t row = 0; row < 2; row++)
            {
                data[row][col] = v[row];
            }
        }

        //行列式
        constexpr T Det()
        {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }

        //余子式
        constexpr T Minor(size_t i, size_t j)
        {
            return data[i][j];
        }

        //代数余子式
        constexpr T Cofactor(size_t row, size_t col)
        {
            return Minor(row, col) * ((row + col) % 2 ? -1 : 1);
        }
    };

    //矩阵重载方法
    //-----------------------------------------------------------------------------
    //M=A*k
    template<size_t N, typename T>
    constexpr Matrix<N, T> operator*(const Matrix<N, T> &A, T k)
    {
        Matrix<N, T> temp;
        for (size_t row = 0; row < N; row++)
        {
            for (size_t col = 0; col < N; col++)
            {
                temp[row][col] = A[row][col] * k;
            }
        }
        return temp;
    }

    //M=k*A
    template<size_t N, typename T>
    constexpr Matrix<N, T> operator*(T k, const Matrix<N, T> &A)
    {
        return A * k;
    }

    //M=A/k
    template<size_t N, typename T>
    constexpr Matrix<N, T> operator/(const Matrix<N, T> &A, T k)
    {
        return A * (1 / k);
    }

    //M=A*B
    template<size_t N, typename T>
    constexpr Matrix<N, T> operator*(const Matrix<N, T> &A, const Matrix<N, T> &B)
    {
        Matrix<N, T> temp;
        for (size_t row = 0; row < N; row++)
        {
            for (size_t col = 0; col < N; col++)
            {
                temp[row][col] = A.Row(row).Dot(B.Col(col));
            }
        }
        return temp;
    }

    //M=A*v
    template<size_t N, typename T>
    constexpr Vector<N, T> operator*(const Matrix<N, T> &A, const Vector<N, T> &v)
    {
        Vector<N, T> temp;
        for (size_t row = 0; row < N; row++)
        {
            temp[row] = v.Dot(A.Row(row));
        }
        return temp;
    }

    //输出
    template<size_t N, typename T>
    std::ostream &operator<<(std::ostream &os, const Matrix<N, T> &A)
    {
        for (size_t row = 0; row < N; row++)
        {
            os << "(";
            for (size_t col = 0; col < N; col++)
            {
                os << A[row][col] << (col < N - 1 ? "," : "");

            }
            os << ")" << "\n";
        }
        return os;
    }

    //矩阵别名
    //-----------------------------------------------------------------------------
    using Matrix3f = Matrix<3, float>;
    using Matrix4f = Matrix<4, float>;
}