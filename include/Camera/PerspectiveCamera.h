#pragma once

#include "Global.h"
#include "Core/Camera.h"

namespace Just {
struct PerspectiveCamera : public ProjectiveCamera {

    PerspectiveCamera(const Transform& cameraToWorld,
                      std::shared_ptr<Film> film,
                      float fov)
            : ProjectiveCamera(cameraToWorld, Perspective(fov, 1e-4f, 1e4f), film) {}

    //从摄像机向视口投射光线
    Ray GenerateRay(const Point2f& sample) const override {
        //相机空间中相机原点为(0,0,0)
        Point3f origin = Point3f(0, 0, 0);
        //在栅格空间中采样的点转到相机空间
        Point3f pCamera = rasterToCamera.TransPoint(Point3f(sample.x, sample.y, 0));
        //计算相机空间下的射线方向
        Vector3f dir = Normalize(pCamera - origin);
        //相机空间下的射线转为世界空间
        return cameraToWorld.TransRay(origin, dir);
    }
};
}