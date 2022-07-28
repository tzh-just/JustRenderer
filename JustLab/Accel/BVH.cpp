
#include <Accel/BVH.h>

namespace just{

void BVH::Divide(size_t n){
  //判断深度和图元数量是否超过符合限制
  if (tree_[n].faces_index.size() < COUNT_FACE_BVH_MIN)
    return;
  if (depth_curr_ > DEPTH_BVH_MAX)
    return;

  //在最长维度排序
  size_t axis = tree_[n].bbox.MajorAxis();
  std::sort(
      tree_[n].faces_index.begin(),
      tree_[n].faces_index.end(),
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
    auto begin = tree_[n].faces_index.begin();
    auto mid = tree_[n].faces_index.begin() + static_cast<int>((tree_[n].faces_index.size()) * i / COUNT_BUCKET);
    auto end = tree_[n].faces_index.end();
    faces_index_left = std::vector<size_t>(begin, mid);
    faces_index_right = std::vector<size_t>(mid, end);

    //合并左右包围盒
    Bounds3f bbox_left, bbox_right;
    for (auto left: faces_index_left){
      bbox_left.Expand(mesh_->GetFaceBBox(left));
    }
    for (auto right: faces_index_right){
      bbox_right.Expand(mesh_->GetFaceBBox(right));
    }

    //计算成本
    float S_LEFT = bbox_left.SurfaceArea();
    float S_RIGHT = bbox_right.SurfaceArea();
    float S_ALL = tree_[n].bbox.SurfaceArea();
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

  //确定子节点的索引
  tree_[n].child = tree_.size();

  //子节点索引入队列，子节点加入树
  queue_.push(tree_.size());
  tree_.emplace_back(node_left);
  queue_.push(tree_.size());
  tree_.emplace_back(node_right);

  count_node_ += 2;
  count_leaf_ += 1;
}


void BVH::Intersect(const Ray3f &ray){

}

}