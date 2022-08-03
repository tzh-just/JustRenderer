//================================================
// 八叉树
//================================================

#pragma once

#include <Accel/Accel.h>

namespace Just
{

    class OctTree : public Accel
    {
    public:

        OctTree(const std::shared_ptr<Mesh>& mesh) : Accel(mesh), minNumFaces(16), maxDepth(12) {}

        void Divide(size_t nodeIndex, std::vector<AccelNode>* children) override;

        bool Traverse(Ray3f* ray, HitRecord* record, bool isShadowRay) const override;
    };

    void OctTree::Divide(size_t nodeIndex, std::vector<AccelNode>* children)
    {
        auto& node = tree[nodeIndex];
        //划分八个子节点的包围盒
        Vector3f center = node.bbox.Centroid();
        for (uint32_t corner = 0; corner < 8; corner++)
        {
            //根据八个拐角点确定子包围盒
            Vector3f subPoint = node.bbox.Corner(corner);
            BoundingBox3f subBBox;
            for (uint32_t d = 0; d < 3; d++)
            {
                subBBox.min[d] = std::min(center[d], subPoint[d]);
                subBBox.max[d] = std::max(center[d], subPoint[d]);
            }

            //分配属于各个子节点的图元
            AccelNode subNode(subBBox);
            for (auto k: node.facesIndexes)
            {
                //检测每个图元与子包围盒是否碰撞
                if (subNode.bbox.Overlaps(mesh->GetFaceBBox(k)))
                {
                    subNode.facesIndexes.emplace_back(k);
                }
            }
            children->emplace_back(subNode);
        }//for遍历八个子包围盒
    }

    bool OctTree::Traverse(Ray3f* ray, HitRecord* record, bool isShadowRay) const
    {

    }
}