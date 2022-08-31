#pragma once

#include <Accel/OctTree.h>

namespace Just {
    void OctTree::Divide(size_t nodeIndex, std::vector<AccelNode>* children) {
        auto& node = tree[nodeIndex];
        //划分八个子节点的包围盒
        Point3f center = node.bbox.Centroid();
        for (int corner = 0; corner < 8; corner++) {
            //根据八个拐角点确定子包围盒
            Point3f subPoint = node.bbox.Corner(corner);
            Bounds3f subBBox;
            for (int d = 0; d < 3; d++) {
                subBBox.pMin[d] = std::min(center[d], subPoint[d]);
                subBBox.pMax[d] = std::max(center[d], subPoint[d]);
            }

            //分配属于各个子节点的图元
            AccelNode subNode(subBBox);
            for (const auto& [meshIndex, faceIndex]: node.indexes) {
                //检测每个图元与子包围盒是否碰撞
                if (Overlaps(subNode.bbox, meshes[meshIndex]->GetFaceBBox(faceIndex))) {
                    subNode.indexes.emplace_back(meshIndex, faceIndex);
                }
            }
            children->emplace_back(subNode);
        }//for遍历八个子包围盒
    }

    bool OctTree::Traverse(const Ray& ray, HitRecord& record, bool isShadowRay) const {

    }
}