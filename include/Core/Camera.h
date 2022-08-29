#pragma once

#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Geometry/Ray.h"

namespace Just {
    struct Camera {
        //相机位置和朝向点
        Point3f origin, target;
        //相机头顶向量
        Vector3f up;
        //宽高比和视场角
        float aspectRatio, fov;
        //近平面和远平面z坐标
        float near, far;
        //近平面y最大坐标和x最大坐标
        float top, right;
        //视口起始位置
        Point3f start;
        //视口宽高
        float width, height;
        //视口宽高向量
        Vector3f horizontal, vertical;

        Camera(const Point3f& origin, const Point3f& target, const Vector3f& up,
               float aspectRatio, float fov, float near, float far)
                : origin(origin), target(target), up(up),
                  aspectRatio(aspectRatio), fov(fov), near(std::abs(near)), far(std::abs(far)) {
            //初始化相机参数
            top = std::tan(Radians(fov * 0.5f)) * near;
            right = top * aspectRatio;
            width = top * 2;
            height = right * 2;

            //
            auto w = Normalize(target - origin);
            auto u = Normalize(Cross(up, w));
            auto v = Cross(w, u);

            horizontal = width * u;
            vertical = height * v;
        }

        //投射光线
        Ray CastRay(int i, int j) {
            Vector3f direction =
            return Ray(origin,)
        }
    };
}