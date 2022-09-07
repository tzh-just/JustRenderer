#pragma once

#include "Global.h"
#include "Core/Camera.h"

namespace Just {
struct PerspectiveCamera : public Camera {
    //视场角
    float fov;
    //近平面y最大坐标和x最大坐标
    float top, right;
    //视口起始位置
    Point3f start;
    //视口宽高
    float width, height;
    //视口宽高向量
    Vector3f horizontal, vertical;


    PerspectiveCamera(const Point3f& origin, const Point3f& target, const Vector3f& up,
                      float near, float far, float aspectRatio, float fov)
            : Camera(origin, target, up, near, far, aspectRatio), fov(fov) {
        //初始化相机参数
        top = std::tan(Radians(fov * 0.5f)) * near;
        right = top * aspectRatio;
        width = top * 2;
        height = right * 2;

        //局部坐标系
        auto w = Normalize(target - origin);
        auto u = Normalize(Cross(up, w));
        auto v = Cross(w, u);

        horizontal = width * u;
        vertical = height * v;

        //图像从左上角开始
        start = origin - horizontal / 2.0f - vertical / 2.0f - Vector3f(0, 0, near);
    }


    //从摄像机向视口投射光线
    float GenerateRay(const Point2f& sample, Ray& ray) const override {
        ray.origin = origin;
        ray.direction = Normalize(start + sample.pFilm.x * horizontal + sample.pFilm.y * vertical - origin);
        return 1;
    }
};
}