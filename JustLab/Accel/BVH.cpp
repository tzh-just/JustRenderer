//================================================
// 层次包围体（二叉树）
//================================================

#pragma once

#include <Accel/Accel.h>

namespace Just
{



    void BVH::Divide(size_t nodeIndex, std::vector<AccelNode>* children)
    {
        auto& node = tree[nodeIndex];

        AccelNode leftNode, rightNode;

        //在最长维度排序
        size_t axis = node.bbox.MajorAxis();
        std::sort(
                node.indexes.begin(),
                node.indexes.end(),
                [this, axis](std::pair<size_t, size_t> left, std::pair<size_t, size_t> right)
                {
                    auto [leftMeshIndex, leftFaceIndex] = left;
                    auto [rightMeshIndex, rightFaceIndex] = right;
                    return meshes[leftMeshIndex]->GetFaceBBox(leftFaceIndex).Centroid()[axis] <
                           meshes[rightMeshIndex]->GetFaceBBox(rightFaceIndex).Centroid()[axis];
                }
        );

        //SAH方法
        float minCost = std::numeric_limits<float>::infinity();
        //分桶
        for (size_t i = 1; i < kNumBuckets; i++)
        {
            auto begin = node.indexes.begin();
            auto mid = node.indexes.begin() + static_cast<int>((node.indexes.size()) * i / kNumBuckets);
            auto end = node.indexes.end();
            auto leftIndexes = std::vector<std::pair<size_t, size_t>>(begin, mid);
            auto rightIndexes = std::vector<std::pair<size_t, size_t>>(mid, end);

            //合并左右包围盒
            BoundingBox3f leftBBox, rightBBox;
            for (const auto& [meshIndex, faceIndex]: leftIndexes)
            {
                leftBBox.ExpandBy(meshes[meshIndex]->GetFaceBBox(faceIndex));
            }
            for (const auto& [meshIndex, faceIndex]: rightIndexes)
            {
                rightBBox.ExpandBy(meshes[meshIndex]->GetFaceBBox(faceIndex));
            }

            //计算成本
            float leftSA = leftBBox.SurfaceArea();
            float rightSA = rightBBox.SurfaceArea();
            float SA = node.bbox.SurfaceArea();
            float cost = 0.125f +                               // TraverseCost
                         leftIndexes.size() * leftSA / SA +     // LeftFacesCount * LeftSurfaceArea/TotalSurfaceArea
                         rightIndexes.size() * rightSA / SA;    // RightFacesCount * RightSurfaceArea/TotalSurfaceArea

            //选取成本最小的分桶方案
            if (cost < minCost)
            {
                minCost = cost;
                leftNode.bbox = leftBBox;
                leftNode.indexes = leftIndexes;
                rightNode.bbox = rightBBox;
                rightNode.indexes = rightIndexes;
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
                    for (const auto& [meshIndex, faceIndex]: node.indexes)
                    {
                        if (meshes[meshIndex]->Intersect(faceIndex, ray))
                        {
                            //阴影测试击中直接返回
                            if (shadow)
                            {
                                return true;
                            }
                            //记录相交信息
                            record->hitTime = ray->hitTime;
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

