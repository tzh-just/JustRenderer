//================================================
// 层次包围体
//================================================

#pragma once

#include <Accel/Accel.h>

namespace just {

struct OctTree : Accel {

  void Build() const override = 0;
  void Intersect(const Ray3f &ray) override = 0;

};

}