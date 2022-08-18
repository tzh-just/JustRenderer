#pragma once

#include <queue>
#include <vector>
#include "Global.h"
#include "Geometry/Ray.h"
#include "Geometry/Bounds3.h"
#include "Hittable/HitRecord.h"
#include "Hittable/Mesh.h"
#include "Accel/AccelNode.h"

namespace Just {
    class Accel {
    protected:
        //网格指针数组
        std::vector<std::shared_ptr<Mesh>> meshes;
        //加速结构树
        std::vector<AccelNode> tree;
        //场景总包围盒
        Bounds3f bbox;
        //场景图元索引
        std::vector<std::pair<int, int>> indexes;

        int currDepth = 1;
        int leafCount = 1;
        int nodeCount = 1;

        int minNumFaces = 0;
        int maxDepth = 0;

    public:

        Accel(int nums, int depth) : minNumFaces(nums), maxDepth(depth) {}

        void AddMesh(const std::shared_ptr<Mesh>& mesh);

        //构建加速结构
        void Build();

        //划分子节点
        virtual void Divide(int n, std::vector<AccelNode>* children) = 0;

        //射线相交测试
        bool Intersect(const Ray& ray, HitRecord* it, bool isShadowRay) const;

        //阴影测试
        bool Intersect(const Ray& ray, bool shadow);

        //遍历子节点
        virtual bool Traverse(Ray* ray, HitRecord* record, bool isShadowRay) const = 0;
    };

    class Naive : public Accel {
    public:

        Naive() : Accel(16, 1) {}

        void Divide(int nodeIndex, std::vector<AccelNode>* children) override;

        bool Traverse(Ray* ray, HitRecord* record, bool isShadowRay) const override;
    };

    class BVH : public Accel {
    protected:
        const int kNumBuckets = 10;
    public:
        BVH() : Accel(16, 32) {}

        void Divide(int nodeIndex, std::vector<AccelNode>* children) override = 0;

        bool Traverse(Ray* ray, HitRecord* record, bool shadow) const override;

    };

    class OctTree : public Accel {
    public:

        OctTree() : Accel(16, 12) {}

        void Divide(int nodeIndex, std::vector<AccelNode>* children) override;

        bool Traverse(Ray* ray, HitRecord* record, bool isShadowRay) const override;
    };
}