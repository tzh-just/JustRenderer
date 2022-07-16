#pragma once

#include "Just/Math/Vector.h"

namespace Just {
    struct Transform {
        Vector3f position;
        Vector3f rotation;
        Vector3f scale;

        Transform() : position(0), rotation(0), scale(1) {}
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    inline std::ostream &operator<<(std::ostream &os, const Transform &trans) {
        return os << "-----------------------------------------------" << std::endl
                  << "position = " << trans.position << std::endl
                  << "rotation = " << trans.rotation << std::endl
                  << "scale    = " << trans.scale << std::endl;
    }
}