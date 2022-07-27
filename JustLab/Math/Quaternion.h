//================================================
// 四元数
//================================================

#pragma once

#include <Math/Vector.h>

namespace just {

template<typename T>
struct Quaternion {
  union {
    struct {
      Vector<3, T> image;
      T real;
    };
    struct {
      T x, y, z, w;
    };
    T data[4];
  };

  Quaternion() = default;

  Quaternion(T real_, const Vector<3, T> &image_) : real(real_), image(image_) {}

  Quaternion(T w_, T x_, T y_, T z_) : w(w_), x(x_), y(y_), z(z_) {}

  T &operator[](int i) {
    assert(i < 4);
    return data[i];
  }

  const T &operator[](int i) const {
    assert(i < 4);
    return data[i];
  }
};


//输出
template<typename T>
inline std::ostream &operator<<(std::ostream &os, const Quaternion<T> &q) {
  return os << "{" << "real: " << q.real << ", image: " << q.image << "}";
}

//共轭
template<typename T>
inline Quaternion<T> Conjugate(const Quaternion<T> &q) {
  return {q.real, -q.image};
}

//逆
template<typename T>
inline Quaternion<T> Invert(const Quaternion<T> &q) {
  return {q.real, -q.image};
}

//归一化
template<typename T>
inline Quaternion<T> Normalize(const Quaternion<T> &q) {
  return {q.real, -q.image};
}

//取模
template<typename T>
inline Quaternion<T> Norm(const Quaternion<T> &q) {
  auto norm = Norm(q.image);
  return std::sqrt(q.real * q.real + Dot(q.image, q.image));
}

//纯四元数
template<typename T>
inline Quaternion<T> Pure(const Quaternion<T> &q) {
  return {0, q.image};
}

//旋转
template<typename T>
inline Matrix<4, 4, T> Rotate(T angle, const Vector<3, T> &axis) {
  angle /= 2;
  Quaternion<T> q(std::cos(Radians(angle)), std::sin(Radians(angle)) * axis);
  return {
      {1 - 2 * q.y * q.y - 2 * q.z * q.z, 2 * q.x * q.y - 2 * q.w * q.z, 2 * q.x * q.z + 2 * q.w * q.y},
      {2 * q.x * q.y + 2 * q.w * q.z, 1 - 2 * q.x * q.x - 2 * q.z * q.z, 2 * q.y * q.z - 2 * q.w * q.x},
      {2 * q.x * q.z - 2 * q.w * q.y, 2 * q.y * q.z + 2 * q.w * q.x, 1 - 2 * q.x * q.x - 2 * q.y * q.y}
  };
}

//加法
template<typename T>
inline Quaternion<T> operator+(const Quaternion<T> &q, T val) {
  return {q.real + val, q.image * val};
}

template<typename T>
inline Quaternion<T> operator+(T val, const Quaternion<T> &q) {
  return {q.real + val, q.image * val};
}

//乘法
template<typename T>
inline Quaternion<T> operator*(const Quaternion<T> &q1, const Quaternion<T> &q2) {
  return {
      q1.real * q2.real - Dot(q1.image, q2.image),
      q1.real * q2.image + q2.real * q1.image + Cross(q1.image, q2.image)
  };
}

}