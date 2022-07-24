//================================================
// 相机
//================================================

#pragma once

#include "../Global.h"
#include "Math/VectorExt.h"
#include "Math/MatrixExt.h"
#include "Math/Transform.h"
#include "Geometry/Ray.h"

namespace Just {

    struct Camera {
    public:
        Vector3f position;
        Vector3f target, up;
        float aspectRatio = 0;
        float near = 0, far = 0;
        float fov = 0;
    public:
        Camera() : position(), target(), up() {};

        virtual Ray3f CastRay() = 0;
    };

}