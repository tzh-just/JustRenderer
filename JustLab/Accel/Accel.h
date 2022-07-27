//================================================
// 空间加速结构
//================================================

#pragma once

#include <vector>
#include <Global.h>
#include <Scene/Ray.h>
#include <Geometry/Bounds.h>

namespace just {

struct AccelNode {
  int child = 0;
  Bounds3f bbox;
  std::vector<int> triangles;

  AccelNode() : bbox() {}
  explicit AccelNode(const Bounds3f &bbox) : bbox(bbox) {}
};

struct Accel {
 public:
  virtual void Build() const = 0;
  virtual void Intersect(const Ray3f &ray) = 0;
 private:
  std::vector<AccelNode> m_tree;
  int depth_max = 0;//最大深度
  int count_leaf = 0;//叶子节点数量
  int count_node = 0;//节点总数
};

}