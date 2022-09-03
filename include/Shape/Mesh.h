#pragma once

#include <vector>
#include "Math/Vector.h"
#include "Geometry/Bounds.h"
#include "Geometry/Hittable.h"
#include "Tools/ParseString.h"
#include "Core/Shape.h"

namespace Just {

struct Vertex {
    size_t p = (size_t) -1;
    size_t uv = (size_t) -1;
    size_t n = (size_t) -1;

    Vertex() = default;

    explicit Vertex(const std::string& str) {
        auto list = ParseString::GetSubStringsByDelimiter(str, "/");

        assert(!list.empty() && list.size() < 3);

        p = ParseString::ToNumeric<size_t>(list[0]);

        if (list.size() >= 2 && !list[1].empty()) {
            uv = ParseString::ToNumeric<size_t>(list[1]);
        }

        if (list.size() >= 3 && !list[2].empty()) {
            n = ParseString::ToNumeric<size_t>(list[2]);
        }
    }

    bool operator==(const Vertex& v) const {
        return v.p == p && v.n == n && v.uv == uv;
    }
};

struct VertexHash {
    std::size_t operator()(const Vertex& v) const {
        size_t hash = std::hash<uint32_t>()(v.p);
        hash = hash * 37 + std::hash<uint32_t>()(v.uv);
        hash = hash * 37 + std::hash<uint32_t>()(v.n);
        return hash;
    }
};

struct Mesh : Shape {
    std::vector<Point3f> positions;
    std::vector<Point<3, size_t>> faces;
    std::vector<Point2f> texcoords;
    std::vector<Vector3f> normals;
    std::vector<Vertex> vertices;

    Mesh(std::shared_ptr<Transform> transform) : Shape(transform) {}

    Bounds3f bounds;

    Bounds3f GetFaceBounds(size_t f);

    bool RayIntersect(const Ray3f& ray, HitRecord& record, size_t f) const;
};

Bounds3f Mesh::GetFaceBounds(size_t f) {
    Bounds3f faceBounds;
    //查询指定三角面的顶点索引
    auto& face = faces[f];
    for (int i = 0; i < 3; ++i) {
        //遍历三角面的顶点确定其包围盒
        auto& point = positions[face[i]];
        faceBounds.Expand(point);
    }
    return faceBounds;
}

bool Mesh::RayIntersect(const Ray3f& ray, HitRecord& record, size_t f) const {
    //读取三角形顶点坐标
    auto& face = faces[f];
    const Point3f& A = positions[face[0]];
    const Point3f& B = positions[face[1]];
    const Point3f& C = positions[face[2]];

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
    if (hitTime <= 0.f || hitTime > ray.tMax) {
        return false;
    }

    ray.tMax = hitTime;
    record.hitTime = hitTime;
    record.point = alpha * A + beta * B + (1 - alpha - beta) * C;
    return true;
}
}