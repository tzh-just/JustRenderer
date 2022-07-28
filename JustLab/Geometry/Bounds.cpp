
#include <Geometry/Bounds.h>

namespace just {

//求包围盒最长的维度
template<typename T>
size_t Bounds<3, T>::MajorAxis() {
  size_t major;
  Vector3f diff = max - min;
  for (size_t i = 1; i < 3; ++i) {
    if (diff[i] > diff[major]) {
      major = i;
    }
  }
  return major;
}

//求包围盒最短的维度
template<typename T>
size_t Bounds<3, T>::MinorAxis() {
  size_t minor;
  Vector3f diff = max - min;
  for (size_t i = 1; i < 3; ++i) {
    if (diff[i] < diff[minor]) {
      minor = i;
    }
  }
  return minor;
}

//求包围盒表面积
template<typename T>
T Bounds<3, T>::SurfaceArea() const {
  T area = 0;
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      if (i != j) {
        area += (max[i] - min[i]) * (max[j] - min[j]);
      }
    }
  }
  return area;
}

//与射线求交
template<typename T>
bool Bounds<3, T>::Intersect(const Ray<3, T> &ray) {

  auto t0 = (min - ray.origin) / ray.direction;
  auto t1 = (max - ray.origin) / ray.direction;

  auto t_min = MinVector(t0, t1);
  auto t_max = MaxVector(t0, t1);

  float t_enter = MaxValue(t_min);
  float t_exit = MinValue(t_max);

  //射线与包围盒不相交或者已经和别的包围盒相交
  if (t_enter > t_exit + kEpsilon ||
      t_exit < 0.0f ||
      t_enter < ray.time) {
    return false;
  }

  return true;
}

//扩展包围盒
template<typename T>
void Bounds<3, T>::Expand(const Bounds<3, T> &bbox) {
  for (size_t i = 0; i < 3; ++i) {
    min[i] = std::min(min[i], bbox.min[i]);
    max[i] = std::max(max[i], bbox.max[i]);
  }
}

template<typename T>
void Bounds<3, T>::Expand(const Vector<3, T> &point) {
  for (size_t i = 0; i < 3; ++i) {
    min[i] = std::min(min[i], point[i]);
    max[i] = std::max(max[i], point[i]);
  }
}

//取包围盒中心点坐标
template<typename T>
Vector<3, T> Bounds<3, T>::Centroid() {
  return (max + min) * 0.5f;
}

//取包围盒拐角点
template<typename T>
Vector<3, T> Bounds<3, T>::Corner(size_t index) {
  Vector<3, T> corner;
  for (size_t i = 0; i < 3; ++i) {
    corner[i] = (index & (1 << i)) ? max[i] : min[i];
  }
  return corner;
}

}