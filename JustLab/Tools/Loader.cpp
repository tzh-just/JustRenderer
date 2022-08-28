#include "Loader.h"

namespace Just{
    void Loader::LoadMesh(TriangleMesh* mesh, const std::string& filePath) {
        std::ifstream fileStream(filePath);
        std::string line;
        while (std::getline(fileStream, line)) {
            std::istringstream strStream(line.c_str());
            char trash;
            if (!line.compare(0, 2, "v ")) {
                strStream >> trash;
                Vector3f position;
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
                Array2f uv;
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
                    face.positionIndexes.push_back(--index);
                    auto a = strStream.str();
                    if (!mesh->uvs.empty()) {
                        strStream >> trash >> index;
                        face.uvIndexes.push_back(--index);
                    }
                    if (!mesh->normals.empty()) {
                        if (mesh->uvs.empty()){
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