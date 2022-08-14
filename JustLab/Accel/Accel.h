//================================================
// 空间加速结构
//================================================

#pragma once

#include <queue>
#include <vector>
#include "Global.h"
#include "Hittable/Ray3.h"
#include "Hittable/Bounds3.h"
#include "Hittable/HitRecord.h"
#include "Hittable/Mesh.h"
#include "Accel/AccelNode.h"

namespace Just
{
    class Accel
    {
    protected:
        //网格指针数组
        std::vector<std::shared_ptr<Mesh>> meshes;
        //加速结构树
        std::vector<AccelNode> tree;
        //场景总包围盒
        BoundingBox3f bbox;
        //场景图元索引
        std::vector<std::pair<size_t,size_t>> indexes;

        int currDepth = 1;
        int leafCount = 1;
        int nodeCount = 1;

        int minNumFaces = 0;
        int maxDepth = 0;

        int maxMeshesCount = 10;

    public:

        void AddMesh(const std::shared_ptr<Mesh> &mesh);

        //构建加速结构
        void Build();

        //划分子节点
        virtual void Divide(size_t n, std::vector<AccelNode>* children) = 0;

        //射线相交测试
        bool Intersect(const Ray3f& ray, HitRecord* it, bool isShadowRay);

        //阴影测试
        bool Intersect(const Ray3f& ray, bool shadow);

        //遍历子节点
        virtual bool Traverse(Ray3f* ray, HitRecord* record, bool isShadowRay) const = 0;
    };

    class Naive : public Accel
    {
    public:

        Naive(const std::shared_ptr<Mesh>& mesh) : Accel(), minNumFaces(16), maxDepth(1) {}

        void Divide(size_t nodeIndex, std::vector<AccelNode>* children) override;

        bool Traverse(Ray3f* ray, HitRecord* record, bool isShadowRay) const override;
    };

    class BVH : public Accel
    {
    protected:
        const size_t kNumBuckets = 10;
    public:
        BVH() : Accel(), minNumFaces(16), maxDepth(32) {}

        void Divide(size_t nodeIndex, std::vector<AccelNode>* children) override = 0;

        bool Traverse(Ray3f* ray, HitRecord* record, bool shadow) const override;

    };

    class OctTree : public Accel
    {
    public:

        OctTree() : Accel(), minNumFaces(16), maxDepth(12) {}

        void Divide(size_t nodeIndex, std::vector<AccelNode>* children) override;

        bool Traverse(Ray3f* ray, HitRecord* record, bool isShadowRay) const override;
    };
}