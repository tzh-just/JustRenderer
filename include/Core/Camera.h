#pragma once

#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Math/Point2.h"
#include "Geometry/Ray.h"
#include "Film.h"

namespace Just {

struct Camera {

    //摄像机空间到世界空间的变换
    Transform cameraToWorld;
    std::shared_ptr<Film> pFilm;

    Camera(const Transform& cameraToWorld, std::shared_ptr<Film> film)
            : cameraToWorld(cameraToWorld), pFilm(film) {}

    //从摄像机向视口投射光线
    virtual Ray GenerateRay(const Point2f& sample) const = 0;
};

struct ProjectiveCamera : public Camera {
    //投影变换
    Transform cameraToScreen;
    //视口变换
    Transform screenToRaster;
    //视口变换的逆变换
    Transform rasterToScreen;
    //投影-视口变换的逆变换
    Transform rasterToCamera;

    ProjectiveCamera(
            const Transform& cameraToWorld,
            const Transform& cameraToScreen,
            std::shared_ptr<Film> film)
            : Camera(cameraToWorld, film), cameraToScreen(cameraToScreen) {
        //宽高比
        float aspect = float(film->resolution.x) / float(film->resolution.y);
        //视口大小
        Bounds2f screen = aspect > 1.0f ? Bounds2f(Point2f(-aspect, -1.0f), Point2f(aspect, 1.0f))
                                        : Bounds2f(Point2f(-1.0f, -1.0f / aspect), Point2f(1.0f, 1.0f / aspect));
        //视口变换
        screenToRaster = Scale(float(film->resolution.x), float(film->resolution.y), 1) *
                         Scale(1.0f / float((screen.pMax.x - screen.pMin.x)),
                               1.0f / float((screen.pMin.y - screen.pMax.y)), 1.0f) *
                         Translate(Vector3f(float(-screen.pMin.x), float(-screen.pMax.y), 0));
        rasterToScreen = Inverse(screenToRaster);
        rasterToCamera = Inverse(cameraToScreen) * rasterToScreen;
    }

    Ray GenerateRay(const Point2f& sample) const override = 0;
};
}