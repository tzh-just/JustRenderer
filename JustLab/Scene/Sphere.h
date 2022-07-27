//================================================
// 球体
//================================================

#pragma once

#include <Global.h>
#include <Math/Vector.h>
#include <Scene/HitRecord.h>
#include <Scene/Ray.h>

namespace just{

struct Sphere {
  Vector3f position;
  float radius;

  Sphere() : position(), radius() {}

  Sphere(const Vector3f &pos_, float r) : position(pos_), radius(r) {}

  bool Intersect(const Ray3f &ray, HitRecord *record) const; //球体与光线求交
};

inline std::ostream &operator<<(std::ostream &os, const Sphere &sphere) {
  return os << sphere.position << ", " << "radius   = " << sphere.radius;
}

}
