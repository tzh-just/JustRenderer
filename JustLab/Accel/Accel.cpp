
#include <Accel/Accel.h>

namespace just {

void Accel::InitMesh(Mesh *mesh) {
  assert(mesh);
  mesh_ = std::make_shared<Mesh>(*mesh);
}

void Accel::Build() {
  if (!mesh_) return;

  //初始化根节点
  auto root = AccelNode(mesh_->bbox, mesh_->faces.size());
  for (size_t i = 0; i < root.faces_index.size(); ++i) {
    root.faces_index[i] = i;
  }

  count_leaf_ = 1;
  count_node_ = 1;
  depth_curr_ = 1;

  //初始化树
  tree_ = std::vector<AccelNode>();
  tree_.emplace_back(root);

  //初始化辅助队列
  queue_ = std::queue<size_t>();
  queue_.push(0);

  auto children = std::vector<AccelNode>();
  auto [COUNT_LIMIT, DEPTH_LIMIT] = GetLimits();
  //构建树
  while (!queue_.empty()) {
    size_t size = queue_.size();//层次遍历
    for (size_t i = 0; i < size; ++i) {
      //判断深度和图元数量是否超过符合限制
      if (tree_[queue_.front()].faces_index.size() > COUNT_LIMIT &&
          depth_curr_ > DEPTH_LIMIT) {
        //设置子节点起始索引
        tree_[queue_.front()].child = tree_.size();
        //检测是否可以分割当前节点的空间
        Divide(queue_.front(), &children);
        --count_leaf_;
        //将分离的子节点加入树，索引入队
        for (auto &child : children) {
          queue_.push(tree_.size());
          tree_.emplace_back(child);
          ++count_leaf_;
          ++count_node_;
        }
      }
      //清理无用数据
      queue_.pop();
      children.clear();
      children.shrink_to_fit();
    }
    depth_curr_++;//记录树深度
  }

  std::cout << "[max depth]: " << depth_curr_ << std::endl;
  std::cout << "[node count]: " << count_node_ << std::endl;
  std::cout << "[leaf count]: " << count_leaf_ << std::endl;
}

void Accel::Intersect(const Ray3f &ray) {

}

}