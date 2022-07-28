
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

  //初始化树
  tree_ = std::vector<AccelNode>();
  tree_.emplace_back(root);

  //初始化辅助队列
  queue_ = std::queue<size_t>();
  queue_.push(0);

  //构建树
  while (!queue_.empty()) {
    size_t size = queue_.size();//层次遍历
    for (size_t i = 0; i < size; ++i) {
      Divide(queue_.front());
      queue_.pop();
    }
    depth_curr_++;//记录树深度
  }

  std::cout << "[max depth: " << depth_curr_ << std::endl;
  std::cout << "[node count]: " << count_node_ << std::endl;
  std::cout << "[leaf count]: " << count_leaf_ << std::endl;
}

void Accel::Intersect(const Ray3f &ray){

}

}