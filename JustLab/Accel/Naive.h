//================================================
// 八叉树
//================================================

#pragma once

#include <Accel/Accel.h>

namespace just
{

    class Naive : public Accel
    {
    public:

        Naive(const Mesh& mesh) : Accel(mesh), minNumFaces(16), maxDepth(1) {}

        void Divide(size_t nodeIndex, std::vector<AccelNode>* children) override;

        bool Traverse(Ray3f* ray, HitRecord* record, bool isShadowRay) const override;
    };

    void Naive::Divide(size_t nodeIndex, std::vector<AccelNode>* children)
    {
        return ;
    }

    bool Naive::Traverse(Ray3f* ray, HitRecord* record, bool isShadowRay) const
    {
        //暴力遍历所有图元进行相交测试
    }
}