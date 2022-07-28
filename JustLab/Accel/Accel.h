//================================================
// 空间加速结构
//================================================

#pragma once

#include <queue>
#include <vector>
#include <Global.h>
#include <Scene/Ray.h>
#include <Geometry/Bounds.h>
#include <Tools/Mesh.h>

namespace just {

struct AccelNode {
  size_t child = 0;
  Bounds3f bbox;
  std::vector<size_t> faces_index;

  AccelNode() : bbox() {}
  explicit AccelNode(const Bounds3f &bbox) : bbox(bbox) {}
  AccelNode(const Bounds3f &bbox, size_t size)
      : bbox(bbox), faces_index(size) {}
};

struct Accel {
 public:

  Accel() : mesh_(), tree_(), queue_() {}

  void Build();

  void InitMesh(Mesh *mesh);

  virtual void Divide(size_t n, std::vector<AccelNode> *children) = 0;

  void Intersect(const Ray3f &ray);

  virtual void Traverse(const Ray3f &ray) = 0;

  virtual std::pair<int, int> GetLimits() = 0;

 protected:
  std::shared_ptr<Mesh> mesh_;
  std::vector<AccelNode> tree_;
  std::queue<size_t> queue_;

  int depth_curr_ = 0;
  int count_leaf_ = 0;
  int count_node_ = 0;
};

}