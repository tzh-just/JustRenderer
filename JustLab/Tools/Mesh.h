
#pragma once

#include <vector>
#include <Math/Vector.h>
#include <Geometry/Bounds.h>

namespace just {


struct Mesh {
  std::vector<Vector3i> faces;
  std::vector<Vector3f> positions;
  std::vector<Vector3f> normals;
  std::vector<Vector2f> uvs;
  Bounds3f bbox;

  Bounds3f GetFaceBBox(size_t index);

};

}