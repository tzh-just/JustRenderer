//================================================
// 射线与几何体相交的信息
//================================================

#pragma once

#include <Global.h>
#include <Math/Vector.h>

namespace just {

struct HitRecord {
  Vector3f position;
  Vector3f normal;

  float time;

  HitRecord() : position(), normal(), time() {}
};

inline std::ostream &operator<<(std::ostream &os, const HitRecord &record) {
  return os << "{position = " << record.position << ", normal   = " << record.normal << "}";
}

}