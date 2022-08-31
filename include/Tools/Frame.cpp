#include "Frame.h"

namespace Just {
    void Frame::CoordinateSystem(const Vector3f& v, Vector3f& other1, Vector3f& other2) {
        if (std::abs(v.x) > std::abs(v.y)) {
            float invLength = 1.0f / std::sqrt(v.x * v.x + v.z * v.z);
            other2 = Vector3f(v.z * invLength, 0.0f, -v.x * invLength);
        } else {
            float invLength = 1.0f / std::sqrt(v.y * v.y + v.z * v.z);
            other1 = Vector3f(0.0f, v.z * invLength, -v.y * invLength);
        }
    }
}