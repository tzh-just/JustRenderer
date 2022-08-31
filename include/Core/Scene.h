#pragma once

#include "Geometry/Bounds3.h"
#include "Accel.h"
#include "Light.h"
#include "Shape.h"

namespace Just {
    struct Scene {
    public:
        Bounds3f bbox;
        std::shared_ptr<Accel> accel;
        std::vector<std::shared_ptr<Mesh>> meshes;
        std::vector<std::shared_ptr<Light>> lights;

        explicit Scene(std::shared_ptr<Accel> accel) : accel(accel) {
            for (auto& mesh: meshes) {
                accel->AddMesh(mesh);
            }
            accel->Build();
        }

        //射线相交测试
        bool RayIntersect(const Ray& ray, HitRecord& record) const {
            return accel->RayIntersect(ray, record, false);
        }

        //阴影射线相交测试
        bool RayIntersect(const Ray& ray) const {
            HitRecord record;
            return accel->RayIntersect(ray, record, true);
        }
    };
}