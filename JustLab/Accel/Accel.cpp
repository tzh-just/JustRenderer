#include "Accel/Accel.h"

namespace Just {
    void Accel::AddMesh(const std::shared_ptr<Mesh>& mesh) {
        meshes.push_back(mesh);
        bbox = Union(bbox, mesh->bbox);
        for (size_t i = 0; i < mesh->faces.size(); i++) {
            indexes.emplace_back(meshes.size() - 1, i);
        }

    }

    void Accel::Build() {
        assert(meshes.size() != 0);

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
        while (!q.empty()) {
            size_t size = q.size();//层次遍历
            for (size_t i = 0; i < size; ++i) {
                auto& node = tree[q.front()];
                //判断深度和图元数量是否超过符合限制
                if (node.indexes.size() > minNumFaces &&
                    currDepth > maxDepth) {
                    //设置子节点起始索引
                    node.child = tree.size();
                    //检测是否可以分割当前节点的空间
                    Divide(q.front(), &children);
                    --leafCount;
                    //将分离的子节点加入树，索引入队
                    for (auto& child: children) {
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
        std::cout << "[pMax depth]: " << currDepth << std::endl;
        std::cout << "[node count]: " << nodeCount << std::endl;
        std::cout << "[leaf count]: " << leafCount << std::endl;
    }

    bool Accel::Intersect(const Ray& ray, HitRecord* it, bool isShadowRay = false) {
        Ray temp = ray;
        bool found = Traverse(&temp, nullptr, false);

        //检测阴影则直接返回相交结果
        if (isShadowRay) {
            return found;
        }

        //记录相交信息
        if (found) {
            //本地坐标系

            //
        }

        return found;
    }

    bool Accel::Intersect(const Ray& ray, bool shadow = true) {
        HitRecord unused;
        return Intersect(ray, &unused, shadow);
    }
}