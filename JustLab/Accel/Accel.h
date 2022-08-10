//================================================
// 空间加速结构
//================================================

#pragma once

#include <queue>
#include <vector>
#include <Global.h>
#include <Geometry/Ray3.h>
#include <Geometry/BoundingBox3.h>
#include <Geometry/HitRecord.h>
#include <Tools/Mesh.h>

namespace Just
{
    struct AccelNode
    {
        size_t child;
        BoundingBox3f bbox;
        std::vector<std::pair<size_t,size_t>> indexes;

        AccelNode() : bbox(), child(0) {}

        explicit AccelNode(const BoundingBox3f& bbox) : bbox(bbox), child(0) {}

        AccelNode(const BoundingBox3f& bbox, size_t size)
                : bbox(bbox), indexes(size), child(0) {}
    };

    class Accel
    {
    protected:
        //网格指针数组
        std::vector<std::shared_ptr<Mesh>> meshes;
        //加速结构树
        std::vector<AccelNode> tree;
        //场景总包围盒
        BoundingBox3f bbox;
        //场景图元索引
        std::vector<std::pair<size_t,size_t>> indexes;

        int currDepth = 1;
        int leafCount = 1;
        int nodeCount = 1;

        int minNumFaces = 0;
        int maxDepth = 0;

        int maxMeshesCount = 10;

    public:

        void AddMesh(const std::shared_ptr<Mesh> &mesh);

        //构建加速结构
        void Build();

        //划分子节点
        virtual void Divide(size_t n, std::vector<AccelNode>* children) = 0;

        //射线相交测试
        bool Intersect(const Ray3f& ray, HitRecord* it, bool isShadowRay);

        //阴影测试
        bool Intersect(const Ray3f& ray, bool shadow);

        //遍历子节点
        virtual bool Traverse(Ray3f* ray, HitRecord* record, bool isShadowRay) const = 0;
    };

    void Accel::AddMesh(const std::shared_ptr<Mesh> &mesh) {
        meshes.push_back(mesh);
        bbox.ExpandBy(mesh->bbox);
        for(size_t i =0;i<mesh->faces.size();i++){
            indexes.emplace_back(meshes.size()-1, i);
        }

    }

    void Accel::Build()
    {
        assert(meshes.size()!=0);

        //初始化根节点
        auto root = AccelNode(bbox, indexes.size());
        root.indexes = indexes;

        //初始化树
        tree = std::vector<AccelNode>();
        tree.emplace_back(root);

        //初始化辅助队列
        std::queue<size_t> q;
        q.push(0);

        //初始化子节点集合
        std::vector<AccelNode> children;

        //构建树
        while (!q.empty())
        {
            size_t size = q.size();//层次遍历
            for (size_t i = 0; i < size; ++i)
            {
                auto& node = tree[q.front()];
                //判断深度和图元数量是否超过符合限制
                if (node.indexes.size() > minNumFaces &&
                    currDepth > maxDepth)
                {
                    //设置子节点起始索引
                    node.child = tree.size();
                    //检测是否可以分割当前节点的空间
                    Divide(q.front(), &children);
                    --leafCount;
                    //将分离的子节点加入树，索引入队
                    for (auto& child: children)
                    {
                        q.push(tree.size());
                        tree.emplace_back(child);
                        ++leafCount;
                        ++nodeCount;
                    }//for遍历子节点
                }
                //清理无用数据
                q.pop();
                children.clear();
                children.shrink_to_fit();
            }//for遍历层
            currDepth++;//记录树深度
        }//while遍历树

        //修正无加速结构时的统计数据
        currDepth = currDepth < maxDepth ? currDepth : maxDepth;

        //统计数据
        std::cout << "[max depth]: " << currDepth << std::endl;
        std::cout << "[node count]: " << nodeCount << std::endl;
        std::cout << "[leaf count]: " << leafCount << std::endl;
    }

    bool Accel::Intersect(const Ray3f& ray, HitRecord* it, bool isShadowRay = false)
    {
        Ray3f temp = ray;
        bool found = Traverse(&temp, nullptr, false);

        //检测阴影则直接返回相交结果
        if (isShadowRay)
        {
            return found;
        }

        //记录相交信息
        if (found)
        {
            //本地坐标系

            //
        }

        return found;
    }

    bool Accel::Intersect(const Ray3f& ray, bool shadow = true)
    {
        HitRecord unused;
        return Intersect(ray, &unused, shadow);
    }

}