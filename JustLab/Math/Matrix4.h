//================================================
// 四阶矩阵
//================================================

#pragma once

#include "Global.h"
#include "Math/Vector4.h"
#include "Math/Matrix3.h"

namespace Just
{
    template<typename T>
    struct Matrix4
    {

        using Matrix = Matrix4<T>;
        using Vector = Vector4<T>;

        T data[4][4];

        constexpr Matrix4()
        {
            for (size_t row = 0; row < 4; row++)
            {
                for (size_t col = 0; col < 4; col++)
                {
                    data[row][col] = 0;
                }
            }
        }

        constexpr Matrix4(const std::initializer_list<Vector>& mat)
        {
            auto it = mat.begin();
            for (size_t row = 0; row < 4; row++)
            {
                SetRow(row, *it++);
            }
        }

        constexpr T* operator[](size_t row)
        {
            assert(row < 4);
            return data[row];
        }

        constexpr const T* operator[](size_t row) const
        {
            assert(row < 4);
            return data[row];
        }

        constexpr Vector Row(size_t row) const
        {
            assert(row < 4);
            Vector temp;
            for (size_t col = 0; col < 4; col++)
            {
                temp[col] = data[row][col];
            }
            return temp;
        }

        constexpr Vector Col(size_t col) const
        {
            assert(col < 4);
            Vector temp;
            for (size_t row = 0; row < 4; row++)
            {
                temp[row] = data[row][col];
            }
            return temp;
        }

        constexpr void SetRow(size_t row, const Vector& v)
        {
            assert(row < 4);
            for (size_t col = 0; col < 4; col++)
            {
                data[row][col] = v[col];
            }
        }

        constexpr void SetCol(size_t col, const Vector& v)
        {
            assert(col < 4);
            for (size_t row = 0; row < 4; row++)
            {
                data[row][col] = v[row];
            }
        }

        //输出
        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
        {
            for (size_t row = 0; row < 4; row++)
            {
                os << mat.Row(row) << "\n";
            }
            return os;
        }

        //数乘
        constexpr Matrix operator*(T k)
        {
            Matrix temp;
            for (size_t row = 0; row < 4; row++)
            {
                for (size_t col = 0; col < 4; col++)
                {
                    temp[row][col] = data[row][col] * k;
                }
            }
            return temp;
        }

        constexpr Matrix operator/(T k)
        {
            Matrix temp;
            for (size_t row = 0; row < 4; row++)
            {
                for (size_t col = 0; col < 4; col++)
                {
                    temp[row][col] = data[row][col] / k;
                }
            }
            return temp;
        }

        //矩阵左乘
        constexpr Matrix operator*(const Matrix& mat)
        {
            Matrix temp;
            for (size_t row = 0; row < 4; row++)
            {
                for (size_t col = 0; col < 4; col++)
                {
                    temp[row][col] = Row(row).Dot(mat.Col(col));
                }
            }
            return temp;
        }

        //列向量左乘
        constexpr Vector operator*(const Vector& v)
        {
            Vector temp;
            for (size_t row = 0; row < 4; row++)
            {
                temp[row] = v.Dot(Row(row));
            }
            return temp;
        }

        //余子式
        constexpr Matrix3<T> Minor(size_t i, size_t j)
        {
            Matrix3<T> minor;
            for (size_t row = 0; row < 3; row++)
            {
                for (size_t col = 0; col < 3; col++)
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
            for (size_t col = 0; col < 4; col++)
            {
                sum += data[0][col] * Cofactor(0, col);
            }
            return sum;
        }

        //转置矩阵
        constexpr Matrix Transpose()
        {
            Matrix transpose;
            for (size_t row = 0; row < 4; row++)
            {
                for (size_t col = 0; col < 4; col++)
                {
                    transpose[col][row] = data[row][col];
                }
            }
            return transpose;
        };

        //伴随矩阵：元素下标对应代数余子式组成的矩阵的转置
        constexpr Matrix Adjoint()
        {
            Matrix adjoint;
            for (size_t row = 0; row < 4; row++)
            {
                for (size_t col = 0; col < 4; col++)
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

    using Matrix4f = Matrix4<float>;

}