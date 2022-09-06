#pragma once

#include <vector>
#include "Math/Vector.h"
#include "Geometry/Bounds.h"
#include "Tools/Parse.h"
#include "Core/Shape.h"
#include "Tools/Frame.h"

namespace Just {

struct Mesh;

struct HitRecord {
    Point3f point;
    Point2f texcoords;
    float hitTime;
    Frame shadingFrame;
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
    std::vector<Point<3, size_t>> faces;
    std::vector<Point2f> texcoords;
    std::vector<Vector3f> normals;

    explicit Mesh(Transform* transform) : Shape(transform) {}

    Bounds3f bounds;

    Bounds3f GetFaceBounds(size_t faceIndex);

    bool RayIntersect(size_t faceIndex, const Ray3f& ray, HitRecord& record) const;
};

Bounds3f Mesh::GetFaceBounds(size_t faceIndex) {
    Bounds3f faceBounds(vertices[faces[faceIndex].x]);
    faceBounds.Expand(vertices[faces[faceIndex].y]);
    faceBounds.Expand(vertices[faces[faceIndex].z]);
    return faceBounds;
}

bool Mesh::RayIntersect(size_t faceIndex, const Ray3f& ray, HitRecord& record) const {
    //读取三角形顶点坐标
    auto& face = faces[faceIndex];
    const Point3f& A = vertices[face[0]];
    const Point3f& B = vertices[face[1]];
    const Point3f& C = vertices[face[2]];

    auto faceNormal = Cross(B - A, C - B);

    //背面剔除
    if (Dot(-ray.direction, faceNormal) < 0) {
        return false;
    }

    // Möller-Trumbore Algorithm
    Vector3f D = ray.direction;
    Vector3f S = ray.origin - A;
    Vector3f E1 = B - A, E2 = C - A;
    Vector3f S1 = Cross(D, E2);
    Vector3f S2 = Cross(S, E1);

    float denom = Dot(S1, E1);

    float hitTime = Dot(S2, E2) / denom;
    float alpha = Dot(S1, S) / denom;
    float beta = Dot(S2, D) / denom;

    //与三角形不相交
    if (alpha < 0.f || beta < 0.f || (alpha + beta) > 1.0f) {
        return false;
    }

    //不是正向第一个相交的三角形
    if (hitTime <= 0.f || hitTime > ray.hitTime) {
        return false;
    }

    ray.hitTime = hitTime;
    record.texcoords = Point2f(alpha, beta);
    return true;
}
}