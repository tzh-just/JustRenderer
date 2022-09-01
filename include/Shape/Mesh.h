#pragma once

#include <vector>

#include "Math/Vector.h"
#include "Geometry/Bounds.h"
#include "Geometry/Hittable.h"

namespace Just {

    struct Face {
        std::vector<int> posIndexes;
        std::vector<int> uvIndexes;
        std::vector<int> normalIndexes;
    };

    struct Mesh {
        std::vector<Point3f> positions;
        std::vector<Face> faces;
        std::vector<Tuple2f> uvs;
        std::vector<Vector3f> normals;

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
            auto& point = positions[face.posIndexes[i]];
            faceBounds.Expand(point);
        }
        return faceBounds;
    }

    bool Mesh::RayIntersect(const Ray3f& ray, HitRecord& record, size_t f) const {
        //读取三角形顶点坐标
        const Face& face = faces[f];
        const Point3f& A = positions[face.posIndexes[0]];
        const Point3f& B = positions[face.posIndexes[1]];
        const Point3f& C = positions[face.posIndexes[2]];

        auto faceNormal = Vector3f::Cross(B - A, C - B);

        //背面剔除
        if (Vector3f::Dot(-ray.direction, faceNormal) < 0) {
            return false;
        }

        // Möller-Trumbore Algorithm
        Vector3f D = ray.direction;
        Vector3f S = ray.origin - A;
        Vector3f E1 = B - A, E2 = C - A;
        Vector3f S1 = Vector3f::Cross(D, E2);
        Vector3f S2 = Vector3f::Cross(S, E1);

        float denom = Vector3f::Dot(S1, E1);

        float hitTime = Vector3f::Dot(S2, E2) / denom;
        float alpha = Vector3f::Dot(S1, S) / denom;
        float beta = Vector3f::Dot(S2, D) / denom;

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