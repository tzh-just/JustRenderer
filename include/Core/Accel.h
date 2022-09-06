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

    int currDepth = 0;
    int leafCount = 1;
    int nodeCount = 1;

    int minNumFaces = 0;
    int maxDepth = 0;

    Accel(int nums, int depth) : minNumFaces(nums), maxDepth(depth) {}

    void AddMesh(std::shared_ptr<Mesh> mesh);

    //构建加速结构
    void Build();

    //划分子节点
    virtual void Divide(size_t nodeIndex, std::vector<AccelNode>& children) = 0;

    //射线相交测试
    bool RayIntersect(const Ray& ray, HitRecord& record, bool isShadow) const;

    //阴影测试
    bool RayIntersect(const Ray& ray, bool shadow) const;

    //遍历子节点
    virtual void Traverse(const Ray& ray, size_t nodeIndex, std::queue<size_t>& queue) const = 0;
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
                Divide(q.front(), children);
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

bool Accel::RayIntersect(const Ray& ray, HitRecord& record, bool isShadow = false) const {
    //初始化辅助队列
    std::queue<size_t> q;
    q.push(0);
    auto [m, f] = std::tuple<size_t, size_t>();
    bool isHit = false;
    //层次遍历树
    while (!q.empty()) {
        auto size = q.size();
        for (int i = 0; i < size; ++i) {
            auto nodeIndex = q.front();
            q.pop();
            //包围盒相交测试
            if (!tree[nodeIndex].bounds.RayIntersect(ray)) {
                continue;
            }
            //节点为叶子节点
            if (tree[nodeIndex].child == 0) {
                float u, v;
                //遍历节点内图元进行相交测试
                for (auto [meshIndex, faceIndex]: tree[nodeIndex].faceIndices) {
                    if (meshes[meshIndex]->RayIntersect(faceIndex, ray, record)) {
                        //阴影测试击中直接返回
                        if (isShadow) {
                            return true;
                        }
                        //记录交点信息
                        record.hitTime = ray.hitTime;
                        record.mesh = meshes[meshIndex];
                        f = faceIndex;
                        isHit = true;
                    }
                }
                //在叶子节点内的图元击中则终止遍历
                if (isHit) {
                    break;
                }
            } else {
                //对非叶子节点继续遍历
                Traverse(ray, nodeIndex, q);
            }
        }
    }

    //阴影射线未击中物体
    if (isShadow) {
        return false;
    }

    //击中物体，插值计算
    if (isHit) {
        auto [alpha, beta, gamma] = std::tuple{
                record.texcoords.x,                             //alpha
                record.texcoords.y,                             //beta
                1 - record.texcoords.x - record.texcoords.y     //gamma
        };

        auto [a, b, c] = std::tuple{
                record.mesh->faces[f].x,    //vertex A
                record.mesh->faces[f].y,    //vertex B
                record.mesh->faces[f].z     //vertex C
        };

        auto p0 = record.mesh->vertices[a];
        auto p1 = record.mesh->vertices[b];
        auto p2 = record.mesh->vertices[c];

        //插值交点三维坐标
        record.point = alpha * p0 + beta * p1 + gamma * p2;

        //插值纹理坐标
        if (!record.mesh->texcoords.empty()) {

            record.texcoords = alpha * record.mesh->texcoords[a] +
                               beta * record.mesh->texcoords[b] +
                               gamma * record.mesh->texcoords[c];
        }

        if (!record.mesh->normals.empty()) {
            //插值法线
            auto normal = alpha * record.mesh->normals[a] +
                          beta * record.mesh->normals[b] +
                          gamma * record.mesh->normals[c];
            record.shadingFrame = Frame(Normalized(normal));
        } else {
            //面法线
            auto faceNormal = Cross(p1 - p0, p2 - p0);
            record.shadingFrame = Frame(Normalized(faceNormal));
        }
    }

    return isHit;
}

bool Accel::RayIntersect(const Ray& ray, bool shadow = true) const {
    HitRecord unused;
    return RayIntersect(ray, unused, shadow);
}
}