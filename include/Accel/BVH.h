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
    //在最长维度排序
    size_t axis = node.bounds.MajorAxis();
    meshes[faceIndices[0].first]->GetFaceBounds(faceIndices[0].second).Centroid()[axis];
    std::sort(
            node.faceIndices.begin(),
            node.faceIndices.end(),
            [this, axis](std::pair<size_t , size_t> left, std::pair<size_t, size_t> right) {
                return meshes[left.first]->GetFaceBounds(left.second).Centroid()[axis] <
                       meshes[right.first]->GetFaceBounds(right.second).Centroid()[axis];
            }
    );

    //SAH方法
    //分桶
    float minCost = std::numeric_limits<float>::infinity();
    AccelNode leftNode, rightNode;
    std::vector<std::pair<size_t, size_t>> leftIndexes, rightIndexes;
    for (int i = 1; i < kNumBuckets; i++) {
        auto begin = node.faceIndices.begin();
        auto mid = node.faceIndices.begin() + (static_cast<int>(node.faceIndices.size()) * i / kNumBuckets);
        auto end = node.faceIndices.end();
        leftIndexes = std::vector<std::pair<size_t, size_t>>(begin, mid);
        rightIndexes = std::vector<std::pair<size_t, size_t>>(mid, end);

        //合并左右包围盒
        Bounds3f leftBounds, rightBounds;
        for (auto [meshIndex, faceIndex]: leftIndexes) {
            leftBounds.Expand(meshes[meshIndex]->GetFaceBounds(faceIndex));
        }
        for (auto [meshIndex, faceIndex]: rightIndexes) {
            rightBounds.Expand(meshes[meshIndex]->GetFaceBounds(faceIndex));
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
            leftNode.faceIndices = leftIndexes;
            rightNode.bounds = rightBounds;
            rightNode.faceIndices = rightIndexes;
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
                for (const auto& [m, f]: node.faceIndices) {
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