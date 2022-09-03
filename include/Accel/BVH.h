#pragma once

#include "Core/Accel.h"

namespace Just {
class BVH : public Accel {
protected:
    const int kNumBuckets = 10;

public:
    BVH() : Accel(16, 32) {}

    void Divide(size_t nodeIndex, std::vector<AccelNode>* children) override;

    bool Traverse(const Ray3f& ray, HitRecord& record, bool shadow) const override;
};

void BVH::Divide(size_t nodeIndex, std::vector<AccelNode>* children) {
    auto& node = tree[nodeIndex];

    AccelNode leftNode, rightNode;

    //在最长维度排序
    int axis = node.bounds.MajorAxis();
    std::sort(
            node.indexes.begin(),
            node.indexes.end(),
            [this, axis](std::pair<int, int> left, std::pair<int, int> right) {
                auto [leftMeshIndex, leftFaceIndex] = left;
                auto [rightMeshIndex, rightFaceIndex] = right;
                return meshes[leftMeshIndex]->GetFaceBounds(leftFaceIndex).Centroid()[axis] <
                       meshes[rightMeshIndex]->GetFaceBounds(rightFaceIndex).Centroid()[axis];
            }
    );

    //SAH方法
    float minCost = std::numeric_limits<float>::infinity();
    //分桶
    for (int i = 1; i < kNumBuckets; i++) {
        auto begin = node.indexes.begin();
        auto mid = node.indexes.begin() + static_cast<int>((node.indexes.size()) * i / kNumBuckets);
        auto end = node.indexes.end();
        auto leftIndexes = std::vector<std::pair<size_t, size_t>>(begin, mid);
        auto rightIndexes = std::vector<std::pair<size_t, size_t>>(mid, end);

        //合并左右包围盒
        Bounds3f leftBounds, rightBounds;
        for (const auto& [m, f]: leftIndexes) {
            leftBounds = Bounds3f::Union(leftBounds, meshes[m]->GetFaceBounds(f));
        }
        for (const auto& [m, f]: rightIndexes) {
            rightBounds = Bounds3f::Union(rightBounds, meshes[m]->GetFaceBounds(f));
        }

        //计算成本
        float leftSA = leftBounds.SurfaceArea();
        float rightSA = rightBounds.SurfaceArea();
        float SA = node.bounds.SurfaceArea();
        float cost = 0.125f +
                     static_cast<float>(leftIndexes.size()) * leftSA / SA +
                     static_cast<float>(rightIndexes.size()) * rightSA / SA;

        //选取成本最小的分桶方案
        if (cost < minCost) {
            minCost = cost;
            leftNode.bounds = leftBounds;
            leftNode.indexes = leftIndexes;
            rightNode.bounds = rightBounds;
            rightNode.indexes = rightIndexes;
        }
    }

    children->emplace_back(leftNode);
    children->emplace_back(rightNode);
}

bool BVH::Traverse(const Ray3f& ray, HitRecord& record, bool shadow) const {
    //初始化辅助队列
    std::queue<size_t> q;
    q.push(0);

    //层次遍历树
    while (!q.empty()) {
        auto size = q.size();
        for (int i = 0; i < size; ++i) {
            auto& node = tree[q.front()];
            q.pop();
            //包围盒相交测试
            if (!node.bounds.RayIntersect(ray)) {
                continue;
            }
            //节点为叶子节点
            if (node.child == 0) {
                //遍历节点得图元进行相交测试
                for (const auto& [m, f]: node.indexes) {
                    if (meshes[m]->RayIntersect(ray, record, f)) {
                        //阴影测试击中直接返回
                        if (shadow) {
                            return true;
                        }
                        return true;
                    }
                }//for遍历图元
            } else {
                //子节点索引入队
                q.push(node.child);
                q.push(node.child + 1);
            }
        }//for遍历层
    }//while遍历树
    return false;
}
}