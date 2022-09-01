
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include <stb/stb_image.h>

#include <Tools/Loader.h>

namespace Just {
    void Loader::LoadTexture(std::shared_ptr<Texture> texture, const std::string& filePath) {
        int width, height, channel;
        //读取纹理
        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channel, 3);

        texture->width = width;
        texture->height = height;

        //转为RGB存入数组
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                unsigned char* rgb = data + (i + height * j);
                texture->pixels.emplace_back((int) rgb[0], (int) rgb[1], (int) rgb[2]);
            }
        }
    }

    void Loader::LoadMesh(std::shared_ptr<Mesh> mesh, const std::string& filePath) {
        std::ifstream fileStream(filePath);
        std::string line;
        while (std::getline(fileStream, line)) {
            std::istringstream strStream(line);
            char trash;
            if (!line.compare(0, 2, "v ")) {
                strStream >> trash;
                Point3f position;
                for (int i = 0; i < 3; ++i) {
                    strStream >> position[i];
                }
                mesh->positions.push_back(position);
            } else if (!line.compare(0, 3, "vn ")) {
                strStream >> trash >> trash;
                Vector3f normal;
                for (int i = 0; i < 3; ++i) {
                    strStream >> normal[i];
                }
                mesh->normals.push_back(normal);
            } else if (!line.compare(0, 3, "vt ")) {
                strStream >> trash >> trash;
                Tuple2f uv;
                for (int i = 0; i < 2; ++i) {
                    strStream >> uv[i];
                }
                mesh->uvs.push_back(uv);
            } else if (!line.compare(0, 2, "f ")) {
                strStream >> trash;
                Face face;
                int index = 0;
                for (int i = 0; i < 3; i++) {
                    strStream >> index;
                    face.posIndexes.push_back(--index);
                    auto a = strStream.str();
                    if (!mesh->uvs.empty()) {
                        strStream >> trash >> index;
                        face.uvIndexes.push_back(--index);
                    }
                    if (!mesh->normals.empty()) {
                        if (mesh->uvs.empty()) {
                            strStream >> trash;
                        }
                        strStream >> trash >> index;
                        face.normalIndexes.push_back(--index);
                    }
                }
                mesh->faces.push_back(face);
            }
        }
    }
}