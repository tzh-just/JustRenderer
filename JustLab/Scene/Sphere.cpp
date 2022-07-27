
#include <Scene/Sphere.h>

namespace just{

bool Sphere::Intersect(const Ray3f &ray, HitRecord *record) const {

  Vector3f op = ray.origin - position;

  float h = Dot(op, ray.direction);//h=b/2
  float det = h * h - Dot(op, op) + radius * radius;

  if (det < 0)
    return false;

  det = sqrt(det);
  record->time = -h - det;

  if (record->time < kEpsilon || record->time > ray.time)
    record->time = -h + det;
  if (record->time < kEpsilon || record->time > ray.time)
    return false;

  record->position = ray.origin + ray.direction * record->time;
  record->normal = Normalize(record->position - position);

  return true;
}

}