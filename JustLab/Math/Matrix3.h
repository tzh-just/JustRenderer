//================================================
// 三阶矩阵
//================================================

#pragma once

#include <Global.h>

#include <Math/Vector3.h>
#include <Math/Matrix2.h>

namespace just
{
    template<typename T>
    struct Matrix3
    {

        using Matrix = Matrix3<T>;
        using Vector = Vector3<T>;

        T data[3][3];

        constexpr Matrix3()
        {
            for (size_t row = 0; row < 3; row++)
            {
                for (size_t col = 0; col < 3; col++)
                {
                    data[row][col] = 0;
                }
            }
        }

        constexpr Matrix3(const std::initializer_list<Vector>& mat)
        {
            auto it = mat.begin();
            for (size_t row = 0; row < 3; row++)
            {
                SetRow(row, *it++);
            }
        }

        constexpr T* operator[](size_t row)
        {
            assert(row < 3);
            return data[row];
        }

        constexpr const T* operator[](size_t row) const
        {
            assert(row < 3);
            return data[row];
        }

        constexpr Vector Row(size_t row) const
        {
            assert(row < 3);
            Vector tmp;
            for (size_t col = 0; col < 3; col++)
            {
                tmp[col] = data[row][col];
            }
            return tmp;
        }

        constexpr Vector Col(size_t col) const
        {
            assert(col < 3);
            Vector tmp;
            for (size_t row = 0; row < 3; row++)
            {
                tmp[row] = data[row][col];
            }
            return tmp;
        }

        constexpr void SetRow(size_t row, const Vector& v)
        {
            assert(row < 3);
            for (size_t col = 0; col < 3; col++)
            {
                data[row][col] = v[col];
            }
        }

        constexpr void SetCol(size_t col, const Vector& v)
        {
            assert(col < 3);
            for (size_t row = 0; row < 3; row++)
            {
                data[row][col] = v[row];
            }
        }

        //输出
        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
        {
            for (size_t row = 0; row < 3; row++)
            {
                os << mat.Row(row) << "\n";
            }
            return os;
        }

        //数乘
        constexpr Matrix operator*(T k)
        {
            Matrix tmp;
            for (size_t row = 0; row < 3; row++)
            {
                for (size_t col = 0; col < 3; col++)
                {
                    tmp[row][col] = data[row][col] * k;
                }
            }
            return tmp;
        }

        constexpr Matrix operator/(T k)
        {
            Matrix tmp;
            for (size_t row = 0; row < 3; row++)
            {
                for (size_t col = 0; col < 3; col++)
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
            for (size_t row = 0; row < 3; row++)
            {
                for (size_t col = 0; col < 3; col++)
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
            for (size_t row = 0; row < 3; row++)
            {
                tmp[row] = v.Dot(Row(row));
            }
            return tmp;
        }

        //余子式
        constexpr Matrix2<T> Minor(size_t i, size_t j)
        {
            Matrix2<T> minor;
            for (size_t row = 0; row < 2; row++)
            {
                for (size_t col = 0; col < 2; col++)
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
            for (size_t col = 0; col < 3; col++)
            {
                sum += data[0][col] * Cofactor(0, col);
            }
            return sum;
        }


        //转置矩阵
        constexpr Matrix Transpose()
        {
            Matrix transpose;
            for (size_t row = 0; row < 3; row++)
            {
                for (size_t col = 0; col < 3; col++)
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
            for (size_t row = 0; row < 3; row++)
            {
                for (size_t col = 0; col < 3; col++)
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

    using Matrix3f = Matrix3<float>;

}