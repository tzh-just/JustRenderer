//================================================
// 矢量模板
//================================================

#pragma once

#include <Global.h>

namespace just {

template<size_t N, typename T>
struct Vector {
  T data[N];

  Vector() {
    for (size_t i = 0; i < N; ++i) {
      data[i] = 0;
    }
  }

  explicit Vector(T val) {
    for (size_t i = 0; i < N; ++i) {
      data[i] = val;
    }
  }

  Vector(const Vector<N, T> &other) {
    for (size_t i = 0; i < N; ++i) {
      data[i] = other.data[i];
    }
  }

  Vector(const std::initializer_list<T> &list) {
    auto it = list.begin();
    for (size_t i = 0; i < N; ++i) {
      data[i] = *it++;
    }
  }

  T &operator[](size_t i) {
    assert(i < N);
    return data[i];
  }

  T operator[](size_t i) const {
    assert(i < N);
    return data[i];
  }
};

template<typename T>
struct Vector<2, T> {
  union {
    struct {
      T x, y;
    };
    T data[2];
  };

  Vector() : x(0), y(0) {}

  explicit Vector(T val) : x(val), y(val) {}

  Vector(T v1, T v2) : x(v1), y(v2) {}

  T &operator[](size_t i) {
    assert(i < 2);
    return data[i];
  }

  T operator[](size_t i) const {
    assert(i < 2);
    return data[i];
  }
};

template<typename T>
struct Vector<3, T> {
  union {
    struct {
      T x, y, z;
    };
    T data[3];
  };

  Vector() : x(0), y(0), z(0) {}

  explicit Vector(T val) : x(val), y(val), z(val) {}

  Vector(T v1, T v2, T v3) : x(v1), y(v2), z(v3) {}

  T &operator[](size_t i) {
    assert(i < 3);
    return data[i];
  }

  T operator[](size_t i) const {
    assert(i < 3);
    return data[i];
  }
};

template<typename T>
struct Vector<4, T> {
  union {
    struct {
      T x, y, z, w;
    };
    T data[4];
  };

  Vector() : x(0), y(0), z(0), w(0) {}

  explicit Vector(T val) : x(val), y(val), z(val), w(val) {}

  Vector(T v1, T v2, T v3, T v4) : x(v1), y(v2), z(v3), w(v4) {}

  T &operator[](size_t i) {
    assert(i < 4);
    return data[i];
  }

  T operator[](size_t i) const {
    assert(i < 4);
    return data[i];
  }

};

//输出
template<size_t N, typename T>
inline std::ostream &operator<<(std::ostream &os, const Vector<N, T> &v) {
  os << "(";
  for (size_t i = 0; i < N; ++i) {
    os << v.data[i];
    if (i + 1 != N)
      os << ",";
  }
  os << ")";
  return os;
}

//取反
template<size_t N, typename T>
inline Vector<N, T> operator-(const Vector<N, T> &v) {
  Vector<N, T> tmp;
  for (size_t i = 0; i < N; ++i) {
    tmp[i] = -v[i];
  }
  return tmp;
}

//加法
template<size_t N, typename T>
inline Vector<N, T> operator+(const Vector<N, T> &v1, const Vector<N, T> &v2) {
  Vector<N, T> tmp;
  for (size_t i = 0; i < N; ++i) {
    tmp[i] = v1[i] + v2[i];
  }
  return tmp;
}

//减法
template<size_t N, typename T>
inline Vector<N, T> operator-(const Vector<N, T> &v1, const Vector<N, T> &v2) {
  Vector<N, T> tmp;
  for (size_t i = 0; i < N; ++i) {
    tmp[i] = v1[i] - v2[i];
  }
  return tmp;
}

//乘法
template<size_t N, typename T>
inline Vector<N, T> operator*(const Vector<N, T> &v1, const Vector<N, T> &v2) {
  Vector<N, T> tmp;
  for (size_t i = 0; i < N; ++i) {
    tmp[i] = v1[i] * v2[i];
  }
  return tmp;
}

//赋值加
template<size_t N, typename T>
inline Vector<N, T> &operator+=(Vector<N, T> &v1, const Vector<N, T> &v2) {
  for (size_t i = 0; i < N; ++i) {
    v1[i] += v2[i];
  }
  return v1;
}

//赋值减
template<size_t N, typename T>
inline Vector<N, T> &operator-=(Vector<N, T> &v1, const Vector<N, T> &v2) {
  for (size_t i = 0; i < N; ++i) {
    v1[i] -= v2[i];
  }
  return v1;
}

//赋值乘
template<size_t N, typename T>
inline Vector<N, T> &operator*=(Vector<N, T> &v1, const Vector<N, T> &v2) {
  for (size_t i = 0; i < N; ++i) {
    v1[i] *= v2[i];
  }
  return v1;
}

//数乘
template<size_t N, typename T, typename U>
inline Vector<N, T> operator*(const Vector<N, T> &v1, U k) {
  Vector<N, T> tmp;
  for (size_t i = 0; i < N; ++i) {
    tmp[i] = v1[i] * static_cast<T>(k);
  }
  return tmp;
}

template<size_t N, typename T, typename U>
inline Vector<N, T> operator*(U k, const Vector<N, T> &v1) {
  Vector<N, T> tmp;
  for (size_t i = 0; i < N; ++i) {
    tmp[i] = v1[i] * static_cast<T>(k);
  }
  return tmp;
}

template<size_t N, typename T, typename U>
inline Vector<N, T> operator/(const Vector<N, T> &v1, U k) {
  Vector<N, T> tmp;
  for (size_t i = 0; i < N; ++i) {
    tmp[i] = v1[i] / static_cast<T>(k);
  }
  return tmp;
}

//赋值数乘
template<size_t N, typename T, typename U>
inline Vector<N, T> &operator*=(Vector<N, T> &v, U k) {
  for (size_t i = 0; i < N; ++i) {
    v[i] *= static_cast<T>(k);
  }
  return v;
}

template<size_t N, typename T, typename U>
inline Vector<N, T> &operator/=(Vector<N, T> &v, U k) {
  for (size_t i = 0; i < N; ++i) {
    v[i] /= static_cast<T>(k);
  }
  return v;
}

//比较
template<size_t N, typename T>
inline bool operator<(const Vector<N, T> &v1, const Vector<N, T> &v2) {
  for (size_t i = 0; i < N; ++i) {
    if (v1[i] >= v2[i]) {
      return false;
    }
  }
  return true;
}

template<size_t N, typename T>
inline bool operator>(const Vector<N, T> &v1, const Vector<N, T> &v2) {
  for (size_t i = 0; i < N; ++i) {
    if (v1[i] <= v2[i]) {
      return false;
    }
  }
  return true;
}

template<size_t N, typename T>
inline bool operator<=(const Vector<N, T> &v1, const Vector<N, T> &v2) {
  for (size_t i = 0; i < N; ++i) {
    if (v1[i] > v2[i]) {
      return false;
    }
  }
  return true;
}

template<size_t N, typename T>
inline bool operator>=(const Vector<N, T> &v1, const Vector<N, T> &v2) {
  for (size_t i = 0; i < N; ++i) {
    if (v1[i] < v2[i]) {
      return false;
    }
  }
  return true;
}

//长度
template<size_t N, typename T>
inline T Length(const Vector<N, T> &v) {
  T sum = 0;
  for (size_t i = 0; i < N; ++i) {
    sum += v[i] * v[i];
  }
  return std::sqrt(sum);
}

//点积
template<size_t N, typename T>
inline T Dot(const Vector<N, T> &v1, const Vector<N, T> &v2) {
  T sum = 0;
  for (size_t i = 0; i < N; ++i) {
    sum += v1[i] * v2[i];
  }
  return sum;
}

//特化二维矢量叉积
template<typename T>
inline T Cross(const Vector<2, T> &v1, const Vector<2, T> &v2) {
  return v1.x * v2.y - v2.x * v1.y;
}

//特化三维矢量叉积
template<typename T>
inline Vector<3, T> Cross(const Vector<3, T> &v1, const Vector<3, T> &v2) {
  return {v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v2.z * v1.x, v1.x * v2.y - v2.x * v1.y};
}

//归一化
template<size_t N, typename T>
inline Vector<N, T> Normalize(const Vector<N, T> &v) {
  T sum = 0;
  for (size_t i = 0; i < N; ++i) {
    sum += v[i] * v[i];
  }
  return v / std::sqrt(sum);
}

//各维度最小值
template<size_t N, typename T>
inline Vector<N, T> MinVector(const Vector<N, T> &v1, const Vector<N, T> &v2) {
  Vector<N, T> min;
  for (size_t i = 0; i < N; ++i) {
    min[i] = std::min(v1[i], v2[i]);
  }
  return min;
}

//各维度最大值
template<size_t N, typename T>
inline Vector<N, T> MaxVector(const Vector<N, T> &v1, const Vector<N, T> &v2) {
  Vector<N, T> max;
  for (size_t i = 0; i < N; ++i) {
    max[i] = std::max(v1[i], v2[i]);
  }
  return max;
}

//插值
template<size_t N, typename T, typename U>
inline Vector<N, T> Lerp(const Vector<N, T> &v1, const Vector<N, T> &v2, U alpha) {
  return v1 * (1 - alpha) + v2;
}

using Vector3i = Vector<3, int>;

using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;
using Vector4f = Vector<4, float>;

}



