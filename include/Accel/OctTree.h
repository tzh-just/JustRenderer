#pragma once

#include "Core/Accel.h"

namespace Just {
class OctTree : public Accel {
public:
    OctTree() : Accel(16, 12) {}

    void Divide(size_t nodeIndex, std::vector <AccelNode>* children) override;

    bool Traverse(const Ray3f& ray, HitRecord& record, bool isShadowRay) const override;
};

void OctTree::Divide(size_t nodeIndex, std::vector <AccelNode>* children) {
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
        for (const auto& [meshIndex, faceIndex]: node.indexes) {
            //检测每个图元与子包围盒是否碰撞
            if (Bounds3f::Overlaps(subNode.bounds, meshes[meshIndex]->GetFaceBounds(faceIndex))) {
                subNode.indexes.emplace_back(meshIndex, faceIndex);
            }
        }
        children->emplace_back(subNode);
    }//for遍历八个子包围盒
}

bool OctTree::Traverse(const Ray3f& ray, HitRecord& record, bool isShadowRay) const {

}
}