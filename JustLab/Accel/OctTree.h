//================================================
// 层次包围体
//================================================

#pragma once

#include <Accel/Accel.h>

namespace just {

struct OctTree : public Accel {

  void Divide(size_t n) override = 0;
  void Intersect(const Ray3f &ray) override = 0;

};

}