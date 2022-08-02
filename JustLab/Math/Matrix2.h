//================================================
// 二阶矩阵
//================================================

#pragma once

#include <Global.h>

#include <Math/Vector2.h>

namespace just
{
    template<typename T>
    struct Matrix2
    {

        using Matrix = Matrix2<T>;
        using Vector = Vector2<T>;

        T data[2][2];

        constexpr Matrix2()
        {
            for (size_t row = 0; row < 2; row++)
            {
                for (size_t col = 0; col < 2; col++)
                {
                    data[row][col] = 0;
                }
            }
        }

        constexpr Matrix2(const std::initializer_list<Vector>& mat)
        {
            auto it = mat.begin();
            for (size_t row = 0; row < 2; row++)
            {
                SetRow(row, *it++);
            }
        }

        constexpr T* operator[](size_t row)
        {
            assert(row < 2);
            return data[row];
        }

        constexpr const T* operator[](size_t row) const
        {
            assert(row < 2);
            return data[row];
        }

        constexpr Vector Row(size_t row) const
        {
            assert(row < 2);
            Vector tmp;
            for (size_t col = 0; col < 2; col++)
            {
                tmp[col] = data[row][col];
            }
            return tmp;
        }

        constexpr Vector Col(size_t col) const
        {
            assert(col < 2);
            Vector tmp;
            for (size_t row = 0; row < 2; row++)
            {
                tmp[row] = data[row][col];
            }
            return tmp;
        }

        constexpr void SetRow(size_t row, const Vector& v)
        {
            assert(row < 2);
            for (size_t col = 0; col < 2; col++)
            {
                data[row][col] = v[col];
            }
        }

        constexpr void SetCol(size_t col, const Vector& v)
        {
            assert(col < 2);
            for (size_t row = 0; row < 2; row++)
            {
                data[row][col] = v[row];
            }
        }

        //输出
        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
        {
            for (size_t row = 0; row < 2; row++)
            {
                os << mat.Row(row) << "\n";
            }
            return os;
        }

        //数乘
        constexpr Matrix operator*(T k)
        {
            Matrix tmp;
            for (size_t row = 0; row < 2; row++)
            {
                for (size_t col = 0; col < 2; col++)
                {
                    tmp[row][col] = data[row][col] * k;
                }
            }
            return tmp;
        }

        constexpr Matrix operator/(T k)
        {
            Matrix tmp;
            for (size_t row = 0; row < 2; row++)
            {
                for (size_t col = 0; col < 2; col++)
                {
                    tmp[row][col] = data[row][col] / k;
                }
            }
            return tmp;
        }
        
        //矩阵左乘
        constexpr Matrix operator*(const Matrix& mat)
        {
            Matrix tmp;
            for (size_t row = 0; row < 2; row++)
            {
                for (size_t col = 0; col < 2; col++)
                {
                    tmp[row][col] = Row(row).Dot(mat.Col(col));
                }
            }
            return tmp;
        }

        //列向量左乘
        constexpr Vector operator*(const Vector& v)
        {
            Vector tmp;
            for (size_t row = 0; row < 2; row++)
            {
                tmp[row] = v.Dot(Row(row));
            }
            return tmp;
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

    using Matrix2f = Matrix2<float>;

}