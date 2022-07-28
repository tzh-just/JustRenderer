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

  virtual void Divide(size_t n) = 0;

  void Intersect(const Ray3f &ray);

  virtual void Traverse(const Ray3f &ray) = 0;

 protected:

  static constexpr size_t COUNT_FACE_OCT_MIN = 16;
  static constexpr size_t COUNT_FACE_BVH_MIN = 16;
  static constexpr size_t DEPTH_OCT_MAX = 12;
  static constexpr size_t DEPTH_BVH_MAX = 32;
  static constexpr size_t COUNT_BUCKET = 10;

  std::shared_ptr<Mesh> mesh_;
  std::vector<AccelNode> tree_;
  std::queue<size_t> queue_;

  int depth_curr_ = 0;
  int count_leaf_ = 0;
  int count_node_ = 0;
};

}