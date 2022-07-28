
#include <Accel/Accel.h>

namespace just {

void Accel::InitMesh(Mesh *mesh) {
  assert(mesh);
  mesh_ = std::make_shared<Mesh>(*mesh);
}

void Accel::Build() {
  assert(mesh_);

  //初始化根节点
  auto root = AccelNode(mesh_->bbox, mesh_->faces.size());
  for (size_t i = 0; i < root.faces_index.size(); ++i) {
    root.faces_index[i] = i;
  }

  //初始化树
  tree_ = std::vector<AccelNode>();
  tree_.emplace_back(root);

  //初始化辅助队列
  std::queue<size_t> q;
  q.push(0);

  //初始化子节点集合
  std::vector<AccelNode> children;

  //获取构建的限制常量
  auto [kMinNumFaces, kMaxDepth] = GetLimits();

  //构建树
  while (!q.empty()) {
    size_t size = q.size();//层次遍历
    for (size_t i = 0; i < size; ++i) {
      auto &node = tree_[q.front()];
      //判断深度和图元数量是否超过符合限制
      if (node.faces_index.size() > kMinNumFaces &&
          depth_curr_ > kMaxDepth) {
        //设置子节点起始索引
        node.child = tree_.size();
        //检测是否可以分割当前节点的空间
        Divide(q.front(), &children);
        --count_leaf_;
        //将分离的子节点加入树，索引入队
        for (auto &child : children) {
          q.push(tree_.size());
          tree_.emplace_back(child);
          ++count_leaf_;
          ++count_node_;
        }
      }
      //清理无用数据
      q.pop();
      children.clear();
      children.shrink_to_fit();
    }
    depth_curr_++;//记录树深度
  }

  //统计数据
  std::cout << "[max depth]: " << depth_curr_ << std::endl;
  std::cout << "[node count]: " << count_node_ << std::endl;
  std::cout << "[leaf count]: " << count_leaf_ << std::endl;
}

bool Accel::Intersect(const Ray3f &ray, HitRecord *it, bool shadow = false) {
  Ray tmp = ray;
  bool found = Traverse(0, &tmp);

  //检测阴影则直接返回相交结果
  if (shadow) {
    return found;
  }

  //记录相交信息
  if (found) {
    //本地坐标系

    //
  }

  return found;
}

bool Accel::Intersect(const Ray3f &ray, bool shadow = true) {
  HitRecord unused;
  return Intersect(ray, &unused, shadow);
}

bool Accel::Traverse(size_t n, Ray3f *ray) {
  auto &node = tree_[n];

  if (!node.bbox.Intersect(*ray)) {
    return false;
  }

  bool hit = false;

  if (node.child == 0) {
    for (auto &f : node.faces_index){

    }
  }
}

}