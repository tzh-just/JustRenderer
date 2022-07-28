//================================================
// 八叉树
//================================================

#pragma once

#include <Accel/Accel.h>

namespace just {

struct OctTree : public Accel {

  void Divide(size_t n, std::vector<AccelNode> *children) override;
  std::pair<size_t, size_t> GetLimits() override;
};

}