//================================================
// 矩阵模板
//================================================

#pragma once

#include <Global.h>
#include <Math/Vector.h>

namespace just {

template<size_t ROW, size_t COL, typename T>
struct Matrix {
  T data[ROW][COL];

  Matrix() {
    for (size_t row = 0; row < ROW; row++) {
      for (size_t col = 0; col < COL; col++) {
        data[row][col] = 0;
      }
    }
  }

  Matrix(const std::initializer_list<Vector<COL, T>> &mat) {
    auto it = mat.begin();
    for (size_t row = 0; row < ROW; row++) {
      SetRow(row, *it++);
    }
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
    for (size_t col = 0; col < COL; col++) {
      tmp[col] = data[row][col];
    }
    return tmp;
  }

  Vector<ROW, T> Col(size_t col) const {
    assert(col < COL);
    Vector<ROW, T> tmp;
    for (size_t row = 0; row < ROW; row++) {
      tmp[row] = data[row][col];
    }
    return tmp;
  }

  void SetRow(size_t row, const Vector<COL, T> &v) {
    assert(row < ROW);
    for (size_t col = 0; col < COL; col++) {
      data[row][col] = v[col];
    }
  }

  void SetCol(size_t col, const Vector<ROW, T> &v) {
    assert(col < COL);
    for (size_t row = 0; row < ROW; row++) {
      data[row][col] = v[row];
    }
  }
};

//输出
template<size_t ROW, size_t COL, typename T>
inline std::ostream &operator<<(std::ostream &os, const Matrix<ROW, COL, T> &mat) {
  for (size_t row = 0; row < ROW; row++) {
    os << "{" << mat.Row(row) << "}" << "\n";
  }
  return os;
}

//加法
template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator+(const Matrix<ROW, COL, T> &mat1, const Matrix<ROW, COL, T> &mat2) {
  Matrix<ROW, COL, T> tmp;
  for (size_t row = 0; row < ROW; row++) {
    for (size_t col = 0; col < COL; col++) {
      tmp[row][col] = mat1[row][col] + mat2[row][col];
    }
  }
  return tmp;
}

//减法
template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator-(const Matrix<ROW, COL, T> &mat1, const Matrix<ROW, COL, T> &mat2) {
  Matrix<ROW, COL, T> tmp;
  for (size_t row = 0; row < ROW; row++) {
    for (size_t col = 0; col < COL; col++) {
      tmp[row][col] = mat1[row][col] - mat2[row][col];
    }
  }
  return tmp;
}

//矩阵左乘
template<size_t ROW, int COM, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator*(const Matrix<ROW, COM, T> &mat1, const Matrix<COM, COL, T> &mat2) {
  Matrix<ROW, COL, T> tmp;
  for (size_t row = 0; row < ROW; row++) {
    for (size_t col = 0; col < COL; col++) {
      tmp[row][col] = Dot(mat1.Row(row), mat2.Col(col));
    }
  }
  return tmp;
}

//列向量左乘
template<size_t ROW, size_t COL, typename T>
inline Vector<ROW, T> operator*(const Matrix<ROW, COL, T> &mat, const Vector<COL, T> &v1) {
  Vector<ROW, T> v2;
  for (size_t row = 0; row < ROW; row++) {
    v2[row] = Dot(v1, mat.Row(row));
  }
  return v2;
}

//数乘
template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator*(const Matrix<ROW, COL, T> &mat, T k) {
  Matrix<ROW, COL, T> tmp;
  for (size_t row = 0; row < ROW; row++) {
    for (size_t col = 0; col < COL; col++) {
      tmp[row][col] = mat[row][col] * k;
    }
  }
  return tmp;
}

template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator*(T k, const Matrix<ROW, COL, T> &mat) {
  Matrix<ROW, COL, T> tmp;
  for (size_t row = 0; row < ROW; row++) {
    for (size_t col = 0; col < COL; col++) {
      tmp[row][col] = mat[row][col] * k;
    }
  }

  return tmp;
}

template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW, COL, T> operator/(const Matrix<ROW, COL, T> &mat, T k) {
  Matrix<ROW, COL, T> tmp;
  for (size_t row = 0; row < ROW; row++) {
    for (size_t col = 0; col < COL; col++) {
      tmp[row][col] = mat[row][col] / k;
    }
  }
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
template<int N, typename T>
inline T Det(const Matrix<N, N, T> &mat) {
  T sum = 0;
  for (size_t col = 0; col < N; col++) {
    sum += mat[0][col] * Cofactor(mat, 0, col);
  }
  return sum;
}

//余子式
template<size_t ROW, size_t COL, typename T>
inline Matrix<ROW - 1, COL - 1, T> Minor(const Matrix<ROW, COL, T> &mat, int i, int j) {
  Matrix<ROW - 1, COL - 1, T> minor;
  for (size_t row = 0; row < ROW - 1; row++) {
    for (size_t col = 0; col < COL - 1; col++) {
      minor[row][col] = mat[row < i ? row : row + 1][col < j ? col : col + 1];
    }
  }
  return minor;
}

//代数余子式
template<int N, typename T>
inline T Cofactor(const Matrix<N, N, T> &mat, size_t row, size_t col) {
  return Det(Minor(mat, row, col)) * ((row + col) % 2 ? -1 : 1);
}

//转置矩阵
template<size_t ROW, size_t COL, typename T>
inline Matrix<COL, ROW, T> Transpose(const Matrix<ROW, COL, T> &mat) {
  Matrix<COL, ROW, T> transpose;
  for (size_t row = 0; row < ROW; row++) {
    for (size_t col = 0; col < COL; col++) {
      transpose[col][row] = mat[row][col];
    }
  }
  return transpose;
};

//伴随矩阵：元素下标对应代数余子式组成的矩阵的转置
template<int N, typename T>
inline Matrix<N, N, T> Adjoint(const Matrix<N, N, T> &mat) {
  Matrix<N, N, T> adjoint;
  for (size_t row = 0; row < N; row++) {
    for (size_t col = 0; col < N; col++) {
      adjoint[col][row] = Cofactor(mat, row, col);
    }
  }
  return adjoint;
}

//逆矩阵
template<int N, typename T>
inline Matrix<N, N, T> Invert(const Matrix<N, N, T> &mat) {
  return Adjoint(mat) / Det(mat);
}

using Matrix4f = Matrix<4, 4, float>;
using Matrix3f = Matrix<3, 3, float>;

}