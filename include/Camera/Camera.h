//================================================
// 相机
//================================================

#pragma once

#include "Global.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Math/Transform.h"
#include "Graphics/Ray.h"

namespace Just {

    struct Camera {
        Transform transform;
        Vector3f target;
        Vector3f up;

        float fov;
        float aspectRatio;
        float near, far;

        Camera(const Vector3f &position_, const Vector3f &target_, float near_, float far_, float fov_, float ratio_)
                : transform(Transform(position_)), target(target_), near(near_), far(far_), fov(fov_), aspectRatio(ratio_) {}

        virtual Ray3f CastRay() = 0 ;
    };

    struct PerspectiveCamera : public Camera {

        Ray3f CastRay () override{}
    };

    struct OrthogonalCamera : public Camera {

        Ray3f CastRay () override{}
    };
}