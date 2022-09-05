#pragma once

#include <queue>
#include <vector>
#include <chrono>

#include "Global.h"
#include "Geometry/Ray.h"
#include "Geometry/Bounds.h"
#include "Shape/Mesh.h"
#include "Tools/Timer.h"

namespace Just {
struct AccelNode {
    size_t child;
    Bounds3f bounds;
    std::vector<std::pair<size_t, size_t>> faceIndices;

    AccelNode() : bounds(), child(0) {}

    explicit AccelNode(const Bounds3f& bounds) : bounds(bounds), child(0) {}

    AccelNode(const Bounds3f& bounds, size_t size)
            : bounds(bounds), faceIndices(size), child(0) {}
};

struct Accel {
    //网格指针数组
    std::vector<std::shared_ptr<Mesh>> meshes;
    //加速结构树
    std::vector<AccelNode> tree;
    //场景总包围盒
    Bounds3f bounds;
    //场景图元索引
    std::vector<std::pair<size_t, size_t>> faceIndices;

    int currDepth = 1;
    int leafCount = 1;
    int nodeCount = 1;

    int minNumFaces = 0;
    int maxDepth = 0;

    Accel(int nums, int depth) : minNumFaces(nums), maxDepth(depth) {}

    void AddMesh(std::shared_ptr<Mesh> mesh);

    //构建加速结构
    void Build();

    //划分子节点
    virtual void Divide(size_t nodeIndex, std::vector<AccelNode>* children) = 0;

    //射线相交测试
    bool RayIntersect(const Ray3f& ray, HitRecord& record, bool isShadow) const;

    //阴影测试
    bool RayIntersect(const Ray3f& ray, bool shadow) const;

    //遍历子节点
    virtual bool Traverse(const Ray3f& ray, HitRecord& record, bool isShadowRay) const = 0;
};

void Accel::AddMesh(std::shared_ptr<Mesh> mesh) {
    std::cout << "Add Mesh" << "\n";
    //更新包围盒
    bounds = Bounds3f::Union(bounds, mesh->bounds);
    //更新顶点索引
    for (int i = 0; i < mesh->faces.size(); i++) {
        faceIndices.emplace_back(meshes.size(), i);
    }
    meshes.push_back(mesh);
}

void Accel::Build() {
    assert(!meshes.empty());
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Build Accel" << "\n";
    //初始化根节点
    auto root = AccelNode(bounds, faceIndices.size());
    root.faceIndices = faceIndices;
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
        auto size = q.size(); //层次遍历
        for (int i = 0; i < size; ++i) {
            auto& node = tree[q.front()];
            //判断深度和图元数量是否超过符合限制
            if (node.faceIndices.size() > minNumFaces && currDepth < maxDepth) {
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
                }
            }
            q.pop();
            children.clear();
            children.shrink_to_fit();
        }
        currDepth++;
    }
    auto over = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(over - start).count();
    std::cout << "[Build time]: " << time << "ms" << std::endl;
    //统计数据
    std::cout << "[Max depth]: " << currDepth << std::endl;
    std::cout << "[Node count]: " << nodeCount << std::endl;
    std::cout << "[Leaf count]: " << leafCount << std::endl;
}

bool Accel::RayIntersect(const Ray3f& ray, HitRecord& record, bool isShadow = false) const {
    //初始化辅助队列
    std::queue<size_t> q;
    q.push(0);
    auto hitFaceIndex = (size_t) -1;
    bool isHit = false;
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
                float u, v;
                //遍历节点内图元进行相交测试
                for (auto [meshIndex, faceIndex]: node.faceIndices) {
                    if (meshes[meshIndex]->RayIntersect(faceIndex, ray, record)) {
                        //阴影测试击中直接返回
                        if (isShadow) {
                            return true;
                        }
                        record.hitTime = ray.hitTime;
                        record.mesh = meshes[meshIndex];
                        hitFaceIndex = faceIndex;
                        isHit = true;
                    }
                }
                //在叶子节点内的图元击中则终止遍历
                if (isHit) {
                    break;
                }
            } else {
                //子节点入队
                q.push(node.child);
                q.push(node.child + 1);
            }
        }
    }
    //阴影射线未击中物体
    if (isShadow) {
        return isHit;
    }
    //记录相交信息
    if (found) {
        //本地坐标系

        //
    }

    return found;
}

bool Accel::RayIntersect(const Ray3f& ray, bool shadow = true) const {
    HitRecord unused;
    return RayIntersect(ray, unused, shadow);
}
}