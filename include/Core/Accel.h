#pragma once

#include <queue>
#include <vector>
#include "Global.h"
#include "Geometry/Ray.h"
#include "Geometry/Bounds3.h"
#include "Geometry/Hittable.h"
#include "Shape/Mesh.h"

namespace Just {
    struct AccelNode {
        size_t child;
        Bounds3f bbox;
        std::vector<std::pair<size_t, size_t>> indexes;

        AccelNode() : bbox(), child(0) {}

        explicit AccelNode(const Bounds3f& bbox) : bbox(bbox), child(0) {}

        AccelNode(const Bounds3f& bbox, size_t size)
                : bbox(bbox), indexes(size), child(0) {}
    };

    struct Accel {
        //网格指针数组
        std::vector<std::shared_ptr<Mesh>> meshes;
        //加速结构树
        std::vector<AccelNode> tree;
        //场景总包围盒
        Bounds3f bbox;
        //场景图元索引
        std::vector<std::pair<size_t, size_t>> indexes;

        int currDepth = 1;
        int leafCount = 1;
        int nodeCount = 1;

        int minNumFaces = 0;
        int maxDepth = 0;

        Accel(int nums, int depth) : minNumFaces(nums), maxDepth(depth) {}

        void AddMesh(std::shared_ptr<Mesh> mesh);

        //构建加速结构
        void Build();

        //划分子节点
        virtual void Divide(size_t nodeIndex, std::vector<AccelNode>* children) = 0;

        //射线相交测试
        bool RayIntersect(const Ray& ray, HitRecord& it, bool isShadowRay) const;

        //阴影测试
        bool RayIntersect(const Ray& ray, bool shadow) const;

        //遍历子节点
        virtual bool Traverse(const Ray& ray, HitRecord& record, bool isShadowRay) const = 0;
    };
}