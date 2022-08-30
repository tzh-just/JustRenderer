#pragma once

#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Geometry/Ray.h"
#include "Film.h"

namespace Just {
    struct Camera {
        //相机位置和朝向点
        Point3f origin, target;
        //相机头顶向量
        Vector3f up;
        //近平面和远平面z坐标
        float near, far;
        //宽高比
        float aspectRatio;
        //成像平面
        const std::shared_ptr<Film> film;

        Camera(const Point3f& origin, const Point3f& target, const Vector3f& up,
               float near, float far, float aspectRatio, std::shared_ptr<Film> film)
                : origin(origin), target(target), up(up),
                  near(std::abs(near)), far(std::abs(far)), aspectRatio(aspectRatio), film(film) {
        }

        //从摄像机向视口投射光线
        virtual Ray CastRay(int i, int j) const = 0;
    };
}