//================================================
// 网格
//================================================

#pragma once

#include <vector>
#include <Math/Vector.h>
#include <Geometry/Bounds.h>

namespace just{

struct Face {
  Vector3f indices[3];
};

struct Mesh {
  std::vector<Face> faces;
  std::vector<Vector3f> positions;
  std::vector<Vector3f> normals;
  std::vector<Vector2f> uvs;
  Bounds3f bbox;
};

}