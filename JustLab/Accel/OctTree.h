//================================================
// 层次包围体
//================================================

#pragma once

#include <Accel/Accel.h>

namespace just {

struct OctTree : public Accel {

  void Divide(size_t n, std::vector<AccelNode> *children) override;
  void Traverse(const Ray3f &ray) override;
  std::pair<int, int> GetLimits() override;
};

}