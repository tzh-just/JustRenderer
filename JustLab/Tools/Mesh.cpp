
#include <Tools/Mesh.h>

namespace just {

Bounds3f Mesh::GetFaceBBox(size_t index) {
  Bounds3f bbox_face;
  //查询指定三角面的顶点索引
  auto &face = faces[index];
  for (int i = 0; i < 3; ++i) {
    //遍历三角面的顶点确定其包围盒
    auto &point = positions[face[i]];
    bbox_face.Expand(point);
  }
  return bbox_face;
}

}