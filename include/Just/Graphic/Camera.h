#pragma once

#include "Just/Global.h"
#include "Just/Math/Vector.h"
#include "Just/Math/Matrix.h"
#include "Transform.h"
#include "Just/Geometry/Ray.h"

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

        Ray3f CastRay(){

        }

        Matrix4f LookAt() {

        }

        virtual Matrix4f Projection() = 0;
    };

    struct PerspectiveCamera : public Camera {
        Matrix4f Projection() override{
            float t = Tan(fov / 2) * n;
            float r = t * aspectRatio;

            return {
                    {n / r, 0,     0,                  0},
                    {0,     n / t, 0,                  0},
                    {0,     0,     -(n + f) / (f - n), -2 * f * n / (f - n)},
                    {0,     0,     -1,                 0}
            };
        }
    };
    struct OrthogonalCamera : public Camera {

    };
}