//================================================
// 层次包围体
//================================================

#pragma once

#include <Accel/Accel.h>

namespace just
{

    class BVH : public Accel
    {
    protected:
        const size_t kNumBuckets = 10;
    public:
        BVH(const Mesh& mesh) : Accel(mesh), minNumFaces(16), maxDepth(32) {}

        void Divide(size_t n, std::vector<AccelNode>* children) override = 0;

        bool Traverse(Ray3f* ray, HitRecord* record, bool shadow) const override;

    };

    void BVH::Divide(size_t n, std::vector<AccelNode>* children)
    {
        auto& node = tree[n];

        AccelNode leftNode, rightNode;

        //在最长维度排序
        size_t axis = node.bbox.MajorAxis();
        std::sort(
                node.facesIndexes.begin(),
                node.facesIndexes.end(),
                [this, axis](size_t f1, size_t f2)
                {
                    return mesh->GetFaceBBox(f1).Centroid()[axis] <
                           mesh->GetFaceBBox(f2).Centroid()[axis];
                }
        );

        //分桶
        float minCost = std::numeric_limits<float>::infinity();
        std::vector<size_t> leftIndexes, rightIndexes;
        for (size_t i = 1; i < kNumBuckets; i++)
        {
            auto begin = node.facesIndexes.begin();
            auto mid = node.facesIndexes.begin() + static_cast<int>((node.facesIndexes.size()) * i / kNumBuckets);
            auto end = node.facesIndexes.end();
            leftIndexes = std::vector<size_t>(begin, mid);
            rightIndexes = std::vector<size_t>(mid, end);

            //合并左右包围盒
            Bounds3f leftBBox, rightBBox;
            for (auto left: leftIndexes)
            {
                leftBBox.ExpandBy(mesh->GetFaceBBox(left));
            }
            for (auto right: rightIndexes)
            {
                rightBBox.ExpandBy(mesh->GetFaceBBox(right));
            }

            //计算成本
            float leftSA = leftBBox.SurfaceArea();
            float rightSA = rightBBox.SurfaceArea();
            float SA = node.bbox.SurfaceArea();
            float cost = 0.125f +
                         static_cast<float>(leftIndexes.size()) * leftSA / SA +
                         static_cast<float>(rightIndexes.size()) * rightSA / SA;

            //选取成本最小的分桶方案
            if (cost < minCost)
            {
                minCost = cost;
                leftNode.bbox = leftBBox;
                leftNode.facesIndexes = leftIndexes;
                rightNode.bbox = rightBBox;
                rightNode.facesIndexes = rightIndexes;
            }
        }

        children->emplace_back(leftNode);
        children->emplace_back(rightNode);
    }


    bool BVH::Traverse(Ray3f* ray, HitRecord* record, bool shadow) const
    {
        //初始化辅助队列
        std::queue<size_t> q;
        q.push(0);

        //层次遍历树
        while (!q.empty())
        {
            auto size = q.size();
            for (int i = 0; i < size; i++)
            {
                auto& node = tree[q.front()];
                q.pop();
                //包围盒相交测试
                if (!node.bbox.Intersect(*ray))
                {
                    continue;
                }
                //节点为叶子节点
                if (node.child == 0)
                {
                    //遍历节点得图元进行相交测试
                    for (auto& f: node.facesIndexes)
                    {
                        if (mesh->Intersect(f, ray))
                        {
                            //阴影测试击中直接返回
                            if (shadow)
                            {
                                return true;
                            }
                            //记录相交信息
                            record->time = ray->time;
                            return true;
                        }
                    }//for遍历图元
                }
                else
                {
                    //子节点索引入队
                    q.push(node.child);
                    q.push(node.child + 1);
                }
            }//for遍历层
        }//while遍历树
    }
}

