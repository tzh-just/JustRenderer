//================================================
// 相机
//================================================

#pragma once

#include "../Global.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Math/Transform.h"
#include "Geometry/Ray.h"

namespace Just {

    class Camera {
    public:
        Transform trans;
        Vector3f target, up;
        float aspectRatio;
        float near, far;
        float fov;
    public:
        Camera(const Vector3f &position_, const Vector3f &target_, const Vector3f &up_, float near_, float far_, float ratio_, float fov_);

        virtual Ray3f CastRay() = 0;
    };

    class PerspectiveCamera : public Camera {
    public:
        Transform trans;
        Vector3f target, up;
        float aspectRatio;
        float near, far;
        float fov;
    public:
        PerspectiveCamera(const Vector3f &position_, const Vector3f &target_, const Vector3f &up_, float near_, float far_, float ratio_, float fov_);

        Ray3f CastRay() override;
    };

    struct OrthogonalCamera : public Camera {

        Ray3f CastRay() override;
    };
}