#pragma once

#include "Geometry/Bounds3.h"
#include "Accel.h"
#include "Light.h"
#include "Integrator.h"
#include "Shape.h"
#include "Camera.h"
#include "Integrator.h"

namespace Just {
    class Scene {
    private:
        Bounds3f bbox;
        Accel* accel;
        Camera* camera;
        std::vector<Mesh*> meshes;
        std::vector<Light*> emitters;

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