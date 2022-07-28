
#include <Accel/OctTree.h>

namespace just {

void OctTree::Divide(size_t n, std::vector<AccelNode> *children) {
  auto & node =  tree_[n];
  //划分八个子节点的包围盒
  Vector3f center = node.bbox.Centroid();
  for (uint32_t corner = 0; corner < 8; corner++) {
    //根据八个拐角点确定子包围盒
    Vector3f point_sub = node.bbox.Corner(corner);
    Bounds3f bbox_sub;
    for (uint32_t d = 0; d < 3; d++) {
      bbox_sub.min[d] = std::min(center[d], point_sub[d]);
      bbox_sub.max[d] = std::max(center[d], point_sub[d]);
    }

    //分配属于各个子节点的图元
    AccelNode node_sub(bbox_sub);
    for (auto k : node.faces_index) {
      //检测每个图元与子包围盒是否碰撞
      if (Overlaps(node_sub.bbox, mesh_->GetFaceBBox(k))) {
        node_sub.faces_index.emplace_back(k);
      }
    }
    children->emplace_back(node_sub);
  }
}
void OctTree::Traverse(const Ray3f &ray) {

}

std::pair<int, int> OctTree::GetLimits() {
  return {16, 12};
}

}