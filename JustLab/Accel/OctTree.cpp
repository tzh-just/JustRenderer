
#include <Accel/OctTree.h>

namespace just {

void OctTree::Divide(size_t n) {

  if (tree_[n].faces_index.size() < COUNT_FACE_OCT_MIN)
    return;
  if (depth_curr_ > DEPTH_OCT_MAX)
    return;

  //设置子节点索引
  tree_[n].child = tree_.size();

  //划分八个子节点的包围盒
  Vector3f center = tree_[n].bbox.Centroid();
  for (uint32_t corner = 0; corner < 8; corner++) {
    //根据八个拐角点确定子包围盒
    Vector3f point_sub = tree_[n].bbox.Corner(corner);
    Bounds3f bbox_sub;
    for (uint32_t d = 0; d < 3; d++) {
      bbox_sub.min[d] = std::min(center[d], point_sub[d]);
      bbox_sub.max[d] = std::max(center[d], point_sub[d]);
    }

    //分配属于各个子节点的图元
    AccelNode node_sub(bbox_sub);
    for (auto k : tree_[n].faces_index){
      //检测每个图元与子包围盒是否碰撞
      if (Overlaps(node_sub.bbox, mesh_->GetFaceBBox(k))){
        node_sub.faces_index.emplace_back(k);
      }

    }

    //辅助队列将子节点索引入队
    queue_.push(tree_.size());
    //将子节点加入树
    tree_.emplace_back(node_sub);
  }

  count_node_ += 8;
  count_node_ += 7;
}
void OctTree::Intersect(const Ray3f &ray) {

}

}