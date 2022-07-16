#pragma once

#include "definition.h"
#include "vector.h"

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
        return os << "Position: | " << trans.position << std::endl
                  << "-----------------------------------------------------------" << std::endl
                  << "Rotation: | " << trans.rotation << std::endl
                  << "-----------------------------------------------------------" << std::endl
                  << "Scale:    | " << trans.scale << std::endl;
    }
}