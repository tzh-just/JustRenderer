//================================================
// 变换
//================================================

#pragma once

#include "Global.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Math/Math.h"

namespace Just {
    struct Transform {
        Vector3f position;
        Vector3f rotation;
        Vector3f scale;

        Transform() : position(0), rotation(0), scale(1) {}

        explicit Transform(const Vector3f &pos) : position(pos), rotation(0), scale(1) {}

        Transform(const Vector3f &position_, const Vector3f &rotation_, const Vector3f &scale_)
                : position(position_), rotation(rotation_), scale(scale_) {}
    };

    //输出
    //----------------------------------------------------------------------------------------------------------
    inline std::ostream &operator<<(std::ostream &os, const Transform &trans) {
        return os << "position = " << trans.position << std::endl
                  << "rotation = " << trans.rotation << std::endl
                  << "scale    = " << trans.scale;
    }


}