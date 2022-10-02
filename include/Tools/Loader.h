#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include "Math/Vector3.h"
#include "Math/Point2.h"
#include "Shape/Mesh.h"
#include "Tools/Texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "stb/stb_image.h"

namespace Just {
class Loader {
public:
    static void LoadTexture(std::shared_ptr<Texture> texture, const std::string& filePath);

    static void LoadMesh(std::shared_ptr<Mesh> mesh, const std::string& filePath);
};

void Loader::LoadTexture(std::shared_ptr<Texture> texture, const std::string& filePath) {
    int width, height, channel;
    //读取纹理
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channel, STBI_rgb);

    //设置纹理大小
    texture->pixels.reserve(width * height);
    texture->width = width;
    texture->height = height;

    //纹理存入数组
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            unsigned char* rgb = data + (i * height + j) * 3;
            texture->pixels.emplace_back(rgb[0], rgb[1], rgb[2]);
        }
    }

    //释放资源
    stbi_image_free(data);
}

//ref: nori
void Loader::LoadMesh(std::shared_ptr<Mesh> mesh, const std::string& filePath) {
    std::ifstream fileStream(filePath);
    std::string line;

    std::unordered_map<Vertex, size_t, VertexHash> vertexMap;
    std::vector<Point3f> positions;
    std::vector<size_t> indices;
    std::vector<Point2f> texcoords;
    std::vector<Vector3f> normals;
    std::vector<Vertex> vertices;

    while (std::getline(fileStream, line)) {
        std::istringstream strStream(line);
        std::string prefix;
        strStream >> prefix;

        if (prefix == "v") {
            Point3f p;
            strStream >> p.x >> p.y >> p.z;
            p = mesh->transform->TransPoint(p);
            positions.push_back(p);
            mesh->bounds.Expand(p);
        } else if (prefix == "vn") {
            Vector3f vn;
            strStream >> vn.x >> vn.y >> vn.z;
            normals.push_back(Normalize(mesh->transform->TransNormal(vn)));
        } else if (prefix == "vt") {
            Point2f vt;
            strStream >> vt.x >> vt.y;
            texcoords.push_back(vt);
        } else if (prefix == "f") {
            std::string v1, v2, v3, v4;
            strStream >> v1 >> v2 >> v3 >> v4;
            Vertex verts[6];
            int vNums = 3;
            verts[0] = Vertex(v1);
            verts[1] = Vertex(v2);
            verts[2] = Vertex(v3);
            if (!v4.empty()) {
                vNums = 6;
                verts[3] = Vertex(v4);
                verts[4] = Vertex(v2);
                verts[5] = Vertex(v3);
            }
            for (int i = 0; i < vNums; i++) {
                const Vertex& v = verts[i];
                //在散列表中查找顶点
                auto it = vertexMap.find(v);
                if (it == vertexMap.end()) {
                    //顶点不存在则在散列表中存储
                    vertexMap[v] = vertices.size();
                    indices.push_back(vertices.size());
                    vertices.push_back(v);
                } else {
                    indices.push_back(it->second);
                }
            }
        }
    }

    mesh->faces.resize(indices.size() / 3);
    memcpy(mesh->faces.data(), indices.data(), sizeof(size_t) * indices.size());

    mesh->vertices.resize(vertices.size());
    for (size_t i = 0; i < vertices.size(); ++i) {
        mesh->vertices[i] = positions.at(vertices[i].p - 1);
    }

    if (!normals.empty()) {
        mesh->normals.resize(vertices.size());
        for (size_t i = 0; i < vertices.size(); ++i) {
            mesh->normals[i] = normals.at(vertices[i].n - 1);
        }
    }

    if (!texcoords.empty()) {
        mesh->uvs.resize(vertices.size());
        for (size_t i = 0; i < vertices.size(); ++i) {
            mesh->uvs[i] = texcoords.at(vertices[i].uv - 1);
        }
    }
}
}