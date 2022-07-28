//================================================
// 边界模板
//================================================

#pragma once

#include <Global.h>
#include <Math/Vector.h>
#include <Scene/Ray.h>

namespace just {

template<size_t N, typename T>
struct Bounds {
  Vector<N, T> min;
  Vector<N, T> max;

  Bounds() : min(MaxValue<T>()), max(MinValue<T>()) {}

  Bounds(const Vector<N, T> &v1, const Vector<N, T> &v2) : min(v1), max(v2) {}
};

template<typename T>
struct Bounds<2, T> {
  Vector<2, T> min;
  Vector<2, T> max;

  Bounds() : min(MaxValue<T>()), max(MinValue<T>()) {}

  Bounds(const Vector<2, T> &v1, const Vector<2, T> &v2) : min(v1), max(v2) {}

};

template<typename T>
struct Bounds<3, T> {

  Vector<3, T> min;
  Vector<3, T> max;

  Bounds() : min(MaxValue<T>()), max(MinValue<T>()) {}

  Bounds(const Vector<3, T> &v1, const Vector<3, T> &v2) : min(v1), max(v2) {}

  bool Intersect(const Ray<3,T> &ray);

  void Expand(const Bounds<3,T> &bbox);

  void Expand(const Vector<3,T> &point);

  Vector<3, T> Centroid();

  Vector<3, T> Corner(size_t index);

  T SurfaceArea() const;

  size_t MajorAxis();

  size_t MinorAxis();
};

//输出
//----------------------------------------------------------------------------------------------------------
template<int N, typename T>
inline std::ostream &operator<<(std::ostream &os, const Bounds<N, T> &bbox) {
  return os << "{" << "min: " << bbox.min << ", max: " << bbox.max << "}";
}

//合并包围盒
template<int N, typename T>
inline Vector<N, T> Union(const Bounds<N, T> &bbox1, const Bounds<N, T> &bbox2) {
  return {MinValue(bbox1.min, bbox1.min), MaxValue(bbox1.max, bbox1.max)};
}

//检测包围盒重叠
template<int N, typename T>
inline bool Overlaps(const Bounds<N, T> &bbox1, const Bounds<N, T> &bbox2) {
  return bbox1.min < bbox1.max && bbox1.max > bbox2.min;
}

using Bounds3f = Bounds<3, float>;

}