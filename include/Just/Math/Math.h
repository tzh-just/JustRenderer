#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace Just {

    //旋转矩阵
    inline Matrix4f XRotationMatrix(float angle) {
        return {
                {1, 0,          0,           0},
                {0, Cos(angle), -Sin(angle), 0},
                {0, Sin(angle), Cos(angle),  0},
                {0, 0,          0,           1}
        };
    }

    //旋转矩阵
    inline Matrix4f YRotationMatrix(float angle) {
        return {
                {Cos(angle),  0, Sin(angle), 0},
                {0,           1, 0,          0},
                {-Sin(angle), 0, Cos(angle), 0},
                {0,           0, 0,          1}
        };
    }

    //旋转矩阵
    inline Matrix4f ZRotationMatrix(float angle) {
        return {
                {Cos(angle), -Sin(angle), 0, 0},
                {Sin(angle), Cos(angle),  0, 0},
                {0,          0,           1, 0},
                {0,          0,           0, 1}
        };
    }

    inline Matrix4f RotationMatrix(float x, float y, float z) {
        return ZRotationMatrix(z) * YRotationMatrix(y) * XRotationMatrix(x);
    }

    inline Matrix4f RotationMatrix(const Vector3f &rotation) {
        return ZRotationMatrix(rotation.z) * YRotationMatrix(rotation.y) * XRotationMatrix(rotation.kx);
    }

    //缩放矩阵
    inline Matrix4f ScaleMatrix(float x, float y, float z) {
        return {
                {x, 0, 0, 0},
                {0, y, 0, 0},
                {0, 0, z, 0},
                {0, 0, 0, 1}
        };
    }

    //缩放矩阵
    inline Matrix4f ScaleMatrix(const Vector3f &scale) {

        return {
                {scale.x, 0,       0,       0},
                {0,       scale.y, 0,       0},
                {0,       0,       scale.z, 0},
                {0,       0,       0,       1}
        };
    }

    //平移矩阵
    inline Matrix4f TranslationMatrix(float x, float y, float z) {
        return {
                {1, 0, 0, x},
                {0, 1, 0, y},
                {0, 0, 1, z},
                {0, 0, 0, 1}
        };
    }

    //平移矩阵
    inline Matrix4f TranslationMatrix(const Vector3f &position) {
        return {
                {1, 0, 0, position.x},
                {0, 1, 0, position.y},
                {0, 0, 1, position.z},
                {0, 0, 0, 1}
        };
    }
}