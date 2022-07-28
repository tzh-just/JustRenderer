
#include <Geometry/Bounds.h>

namespace just {

template<int N, typename T>
//求包围盒最长的维度
size_t Bounds<N, T>::MajorAxis() {
  T major;
  Vector3f diff = max - min;
  for (int i = 1; i < N; ++i) {
    if (diff[i] > diff[major]) {
      major = i;
    }
  }
  return major;
}

//求包围盒最短的维度
template<int N, typename T>
size_t Bounds<N, T>::MinorAxis() {
  T minor;
  Vector3f diff = max - min;
  for (int i = 1; i < N; ++i) {
    if (diff[i] < diff[minor]) {
      minor = i;
    }
  }
  return minor;
}

template<int N, typename T>
//求包围盒表面积
T Bounds<N, T>::SurfaceArea() {
  T area = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i != j) {
        area += (max[i] - min[i]) * (max[j] - min[j]);
      }
    }
  }
  return area;
}

//与射线求交
template<int N, typename T>
bool Bounds<N, T>::Intersect(const Ray3f &ray) {
  return false;
}

//扩展包围盒
template<int N, typename T>
void Bounds<N, T>::Expand(const Bounds &bbox) {
  for (int i = 0; i < N; ++i) {
    min[i] = std::min(min[i], bbox.min[i]);
    max[i] = std::max(max[i], bbox.max[i]);
  }
}

template<int N, typename T>
void Bounds<N, T>::Expand(const Vector3f &point) {
  for (int i = 0; i < N; ++i) {
    min[i] = std::min(min[i], point[i]);
    max[i] = std::max(max[i], point[i]);
  }
}

//取包围盒中心点坐标
template<int N, typename T>
Vector<N, T> Bounds<N, T>::Centroid() {
  return (max + min) * 0.5f;
}

//取包围盒拐角点
template<int N, typename T>
Vector<N, T> Bounds<N, T>::Corner(size_t index) {
  Vector<N, T> corner;
  for (size_t i = 0; i < N; ++i) {
    corner[i] = (index & (1 << i)) ? max[i] : min[i];
  }
  return corner;
}
}