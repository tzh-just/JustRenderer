#include <Renderer/Camera.h>

namespace Just {

    PerspectiveCamera::PerspectiveCamera(const Vector3f &position_, const Vector3f &target_, const Vector3f &up_, float near_, float far_, float ratio_, float fov_)
            : trans(Transform(position_)),
              target(target_), up(up_),
              near(near_), far(far_),
              aspectRatio(ratio_),
              fov(fov_) {}

    Ray3f PerspectiveCamera::CastRay() {
        Ray3f ray;
        return ray;
    }

}