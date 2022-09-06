#pragma once

#include "Core/Accel.h"

namespace Just {
class OctTree : public Accel {
public:
    OctTree() : Accel(16, 12) {}

    void Divide(size_t nodeIndex, std::vector<AccelNode>& children) override;

    void Traverse(const Ray3f& ray, size_t nodeIndex, std::queue<size_t>& queue) const override;
};

void OctTree::Divide(size_t nodeIndex, std::vector<AccelNode>& children) {
    auto& node = tree[nodeIndex];
    //划分八个子节点的包围盒
    Point3f center = node.bounds.Centroid();
    for (int corner = 0; corner < 8; corner++) {
        //根据八个拐角点确定子包围盒
        Point3f subPoint = node.bounds.Corner(corner);
        Bounds3f subBounds;
        for (int d = 0; d < 3; d++) {
            subBounds.pMin[d] = std::min(center[d], subPoint[d]);
            subBounds.pMax[d] = std::max(center[d], subPoint[d]);
        }

        //分配属于各个子节点的图元
        AccelNode subNode(subBounds);
        for (const auto& [meshIndex, faceIndex]: node.faceIndices) {
            //检测每个图元与子包围盒是否碰撞
            if (Bounds3f::Overlaps(subNode.bounds, meshes[meshIndex]->GetFaceBounds(faceIndex))) {
                subNode.faceIndices.emplace_back(meshIndex, faceIndex);
            }
        }
        children.emplace_back(subNode);
    }
}

void OctTree::Traverse(const Ray3f& ray, size_t nodeIndex, std::queue<size_t>& queue) const {
    //初始化子节点索引
    size_t children[8];
    for (size_t i = 0; i < 8; i++) {
        children[i] = tree[nodeIndex].child + i;
    }
    //根据子节点包围盒中心点与光线起始点的距离（平方）进行排序
    std::sort(
            children,
            children + 8,
            [*this, ray](size_t l, size_t r) {
                return LengthSqrt(tree[l].bounds.Centroid() - ray.origin) <
                       LengthSqrt(tree[r].bounds.Centroid() - ray.origin);
            }
    );
    //排序后的子节点入队，距离近的优先进行相交测试
    for (unsigned long long & i : children) {
        queue.push(i);
    }
}
}