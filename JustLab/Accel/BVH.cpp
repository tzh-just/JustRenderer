
#include <Accel/BVH.h>

namespace just {

void BVH::Divide(size_t n, std::vector<AccelNode> *children) {
  auto & node =  tree_[n];

  //在最长维度排序
  size_t axis = node.bbox.MajorAxis();
  std::sort(
      node.faces_index.begin(),
      node.faces_index.end(),
      [this, axis](size_t f1, size_t f2) {
        return mesh_->GetFaceBBox(f1).Centroid()[axis] <
            mesh_->GetFaceBBox(f2).Centroid()[axis];
      }
  );

  //分桶
  float cost_min = std::numeric_limits<float>::infinity();
  AccelNode node_left, node_right;
  std::vector<size_t> faces_index_left, faces_index_right;
  for (size_t i = 1; i < COUNT_BUCKET; i++) {
    auto begin = node.faces_index.begin();
    auto mid = node.faces_index.begin() + static_cast<int>((node.faces_index.size()) * i / COUNT_BUCKET);
    auto end = node.faces_index.end();
    faces_index_left = std::vector<size_t>(begin, mid);
    faces_index_right = std::vector<size_t>(mid, end);

    //合并左右包围盒
    Bounds3f bbox_left, bbox_right;
    for (auto left : faces_index_left) {
      bbox_left.Expand(mesh_->GetFaceBBox(left));
    }
    for (auto right : faces_index_right) {
      bbox_right.Expand(mesh_->GetFaceBBox(right));
    }

    //计算成本
    float S_LEFT = bbox_left.SurfaceArea();
    float S_RIGHT = bbox_right.SurfaceArea();
    float S_ALL = node.bbox.SurfaceArea();
    float cost = 0.125f +
        static_cast<float>(faces_index_left.size()) * S_LEFT / S_ALL +
        static_cast<float>(faces_index_right.size()) * S_RIGHT / S_ALL;

    //选取成本最小的分桶方案
    if (cost < cost_min) {
      cost_min = cost;
      node_left.bbox = bbox_left;
      node_left.faces_index = faces_index_left;
      node_right.bbox = bbox_right;
      node_right.faces_index = faces_index_right;
    }
  }

  children->emplace_back(node_left);
  children->emplace_back(node_right);
}

void BVH::Traverse(const Ray3f &ray) {

}

std::pair<int, int> BVH::GetLimits() {
  return {12, 32};
}

}