#pragma once

#include "Math/Vector.h"
#include "Geometry/Ray.h"
#include "Film.h"

namespace Just {
struct CameraSample {
    Point2f pFilm;
    Point2f pLens;
    float time;

    CameraSample() : time(0) {};
};

struct Camera {

    //相机位置和朝向点
    Point3f origin, target;
    //相机头顶向量
    Vector3f up;
    //近平面和远平面z坐标
    float near, far;
    //宽高比
    float aspectRatio;

    Camera(const Point3f& origin, const Point3f& target, const Vector3f& up,
           float near, float far, float aspectRatio)
            : origin(origin), target(target), up(up),
              near(std::abs(near)), far(std::abs(far)), aspectRatio(aspectRatio) {
    }

    //从摄像机向视口投射光线
    virtual float GenerateRay(const CameraSample& sample, Ray& ray) const = 0;
};
}