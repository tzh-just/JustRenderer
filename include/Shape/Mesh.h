#pragma once

#include <vector>
#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Geometry/Bounds.h"
#include "Tools/Parse.h"
#include "Core/Shape.h"
#include "Tools/Frame.h"

namespace Just {

struct Mesh;

struct HitRecord {
    Point3f point;
    Point2f uv;
    float hitTime;
    Frame shadingFrame;
    Frame geometryFrame;
    std::shared_ptr<Mesh> mesh;

    HitRecord() : hitTime(0) {}
};

struct Vertex {
    size_t p = (size_t) -1;
    size_t uv = (size_t) -1;
    size_t n = (size_t) -1;

    Vertex() = default;

    explicit Vertex(const std::string& str) {
        auto list = Parse::Tokenize(str, "/", true);

        assert(!list.empty() && list.size() <= 3);

        p = Parse::ToNumeric<size_t>(list[0]);

        if (list.size() >= 2 && !list[1].empty()) {
            uv = Parse::ToNumeric<size_t>(list[1]);
        }

        if (list.size() >= 3 && !list[2].empty()) {
            n = Parse::ToNumeric<size_t>(list[2]);
        }
    }

    bool operator==(const Vertex& v) const {
        return v.p == p && v.n == n && v.uv == uv;
    }
};

//ref: nori
struct VertexHash {
    std::size_t operator()(const Vertex& v) const {
        size_t hash = std::hash<size_t>()(v.p);
        hash = hash * 37 + std::hash<size_t>()(v.uv);
        hash = hash * 37 + std::hash<size_t>()(v.n);
        return hash;
    }
};

struct Mesh : Shape {
    std::vector<Point3f> vertices;
    std::vector<Point3<size_t>> faces;
    std::vector<Point2f> uvs;
    std::vector<Vector3f> normals;

    explicit Mesh(std::shared_ptr<Transform> transform) : Shape(transform) {}

    Bounds3f bounds;

    Bounds3f GetFaceBounds(size_t faceIndex);

    bool RayIntersect(size_t faceIndex, const Ray& ray, HitRecord& record) const;
};

Bounds3f Mesh::GetFaceBounds(size_t faceIndex) {
    Bounds3f faceBounds(vertices[faces[faceIndex].x]);
    faceBounds.Expand(vertices[faces[faceIndex].y]);
    faceBounds.Expand(vertices[faces[faceIndex].z]);
    return faceBounds;
}

bool Mesh::RayIntersect(size_t faceIndex, const Ray& ray, HitRecord& record) const {
    //读取三角形顶点坐标
    auto& face = faces[faceIndex];
    const Point3f& p0 = vertices[face[0]];
    const Point3f& p1 = vertices[face[1]];
    const Point3f& p2 = vertices[face[2]];

    const Vector3f edge1 = p1 - p0;
    const Vector3f edge2 = p2 - p0;

    //计算交点
    const Vector3f pvec = Cross(ray.direction, edge2);
    float det = Dot(edge1, pvec);
    if (det < 1e-8f && det > -1e-8f) {
        return false;
    }
    float invDet = 1.0f / det;

    const Vector3f tvec = ray.origin - p0;

    const float u = Dot(tvec, pvec) * invDet;
    if (u < 0.0f || u > 1.0f) {
        return false;
    }

    const Vector3f qvec = Cross(tvec, edge1);

    const float v = Dot(ray.direction, qvec) * invDet;

    if (v < 0.0f || u + v > 1.0f) {
        return false;
    }

    const float t = Dot(edge2, qvec) * invDet;

    if (t < 0 || t > ray.tMax) {
        return false;
    }

    ray.tMax = t;
    record.hitTime = t;
    record.uv = Point2f(u, v);
    return true;
}
}