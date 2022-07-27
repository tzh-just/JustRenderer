#pragma once

#include <vector>

#include "Geometry/Bounds.h"
#include "Accel.h"

namespace Just {

    struct OctTreeNode {
        int child = 0;
        Bounds3f bbox;
        std::vector<int> indices;
        OctTreeNode() : bbox() {}
        explicit OctTreeNode(Bounds3f bbox) : bbox(std::move(bbox)) {}
    };

    class OctTree  : Accel{
    private:
        std::vector<OctTreeNode> m_tree;
        int m_maxDepth = 0;//最大深度
        int m_leafCount = 0;//叶子节点数量
        int m_nodeCount = 0;//节点总数
    public:
        void Build(){

        }
    };
}


