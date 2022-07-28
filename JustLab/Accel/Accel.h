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
#include "Scene/HitRecord.h"

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

  void Build();

  void InitMesh(Mesh *mesh);

  virtual void Divide(size_t n, std::vector<AccelNode> *children) = 0;

  bool Intersect(const Ray3f &ray, HitRecord *it, bool shadow);

  bool Intersect(const Ray3f &ray, bool shadow);

  bool Traverse(size_t n, Ray3f *ray);

  virtual std::pair<size_t, size_t> GetLimits() = 0;

 protected:
  std::shared_ptr<Mesh> mesh_;
  std::vector<AccelNode> tree_;

  int depth_curr_ = 1;
  int count_leaf_ = 1;
  int count_node_ = 1;
};

}