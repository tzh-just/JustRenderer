//================================================
// 层次包围体
//================================================

#pragma once

#include <Accel/Accel.h>

namespace just {

class BVH : public Accel {
 public:
  void Divide(size_t n, std::vector<AccelNode> *children) override = 0;
  void Traverse(const Ray3f &ray) override;
  std::pair<int, int> GetLimits() override;
 protected:
  size_t COUNT_BUCKET = 10;
};
}