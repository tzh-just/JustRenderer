//================================================
// 层次包围体
//================================================

#pragma once

#include <Accel/Accel.h>

namespace just {

enum BVHMode{
  BVH = 0x01,
  SAH = 0x02,
};

class BVH : public Accel {
 public:
  void Divide(size_t n, std::vector<AccelNode> *children) override = 0;
  void DivideBySAH(AccelNode *node, AccelNode *node_left, AccelNode *node_right);
  std::pair<size_t, size_t> GetLimits() override;

  BVHMode mode = BVHMode::SAH;
 protected:
  const size_t kNumBuckets = 10;
};
}