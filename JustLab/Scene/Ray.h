//================================================
// 射线模板
//================================================

#pragma once

#include <Math/Vector.h>

namespace just {

template<int N, typename T>
struct Ray {
  Vector<N, T> origin;
  Vector<N, T> direction;
  union{
    T distance;
    T time;
  };


  Ray() : origin(), direction(), distance() {}

  Ray(const Vector<N, T> &orig, const Vector<N, T> &dir) : origin(orig), direction(dir) {}
};

template<int N, typename T>
inline std::ostream &operator<<(std::ostream &os, const Ray<N, T> &ray) {
  return os << "origin    = " << ray.origin << ", " << "direction = " << ray.direction;
}

using Ray3f = Ray<3, float>;

}
