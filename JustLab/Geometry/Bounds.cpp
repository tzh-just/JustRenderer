
#include <Geometry/Bounds.h>

namespace just {

template<int N, typename T>
bool Bounds<N, T>::Intersect(const Ray3f &ray) {
  return false;
}

template<int N, typename T>
void Bounds<N, T>::Expand(const Bounds &bbox) {
  for (int i = 0; i < N; ++i) {
    min[i] = std::min(min[i], bbox.min[i]);
    max[i] = std::max(max[i], bbox.max[i]);
  }
}
}