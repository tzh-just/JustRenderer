
#include "Renderer/Camera.h"

namespace Just{
    struct OrthogonalCamera : public Camera {

        Ray3f CastRay () override;
    };
}

