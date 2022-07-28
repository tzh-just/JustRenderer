//================================================
// 边界模板
//================================================

#pragma once

#include <Global.h>
#include <Math/Vector.h>
#include <Scene/Ray.h>

namespace just{

template<int N, typename T>
struct Bounds {
  Vector<N, T> min;
  Vector<N, T> max;

  Bounds() : min(MaxValue<T>()), max(MinValue<T>()) {}

  Bounds(const Vector<N, T> &v1, const Vector<N, T> &v2) : min(v1), max(v2) {}

  bool Intersect(const Ray3f &ray);

  void Expand(const Bounds &bbox);

  void Expand(const Vector3f &point);

  Vector<N, T> Centroid();

  Vector<N, T> Corner(size_t index);

  T SurfaceArea() const;

  size_t MajorAxis() const;

  size_t MinorAxis() const;
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