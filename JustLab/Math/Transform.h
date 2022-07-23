//================================================
// 数学工具函数
//================================================

#pragma once

#include "../Global.h"
#include "Vector.h"
#include "Matrix.h"
#include "Transform.h"

namespace Just::Transform {

    //旋转矩阵
    inline Matrix4f Rotate(float x, float y, float z) {
        Matrix4f matX{
                {Cos(y),  0, Sin(y), 0},
                {0,       1, 0,      0},
                {-Sin(y), 0, Cos(y), 0},
                {0,       0, 0,      1}
        };
        Matrix4f matY{
                {Cos(y),  0, Sin(y), 0},
                {0,       1, 0,      0},
                {-Sin(y), 0, Cos(y), 0},
                {0,       0, 0,      1}
        };
        Matrix4f matZ{
                {1, 0,      0,       0},
                {0, Cos(x), -Sin(x), 0},
                {0, Sin(x), Cos(x),  0},
                {0, 0,      0,       1}
        };
        return matZ * matY * matZ;
    }

    inline Matrix4f Rotate(const Vector3f &rotation) {
        return Rotate(rotation.x, rotation.y, rotation.z);
    }

    inline Matrix4f Rotate(const Vector3f &i, const Vector3f &j, const Vector3f &k) {
        return {
                {i.x, j.x, k.x, 0},
                {i.y, j.y, k.y, 0},
                {i.z, j.z, k.z, 0},
                {0,   0,   0,   1}
        };
    }

    //缩放矩阵
    inline Matrix4f Scale(float x, float y, float z) {
        return {
                {x, 0, 0, 0},
                {0, y, 0, 0},
                {0, 0, z, 0},
                {0, 0, 0, 1}
        };
    }

    //缩放矩阵
    inline Matrix4f Scale(const Vector3f &scale) {

        return {
                {scale.x, 0,       0,       0},
                {0,       scale.y, 0,       0},
                {0,       0,       scale.z, 0},
                {0,       0,       0,       1}
        };
    }

    //平移矩阵
    inline Matrix4f Translate(float x, float y, float z) {
        return {
                {1, 0, 0, x},
                {0, 1, 0, y},
                {0, 0, 1, z},
                {0, 0, 0, 1}
        };
    }

    //平移矩阵
    inline Matrix4f Translate(const Vector3f &position) {
        return {
                {1, 0, 0, position.x},
                {0, 1, 0, position.y},
                {0, 0, 1, position.z},
                {0, 0, 0, 1}
        };
    }

    inline Matrix4f ObjectToWorld(const Vector3f &position, const Vector3f &scale, const Vector3f &rotation) {
        return Translate(position) * Scale(scale) * Rotate(rotation);
    }

    //视图矩阵
    inline Matrix4f LookAt(const Vector3f &origin, const Vector3f &target, const Vector3f &up) {
        Vector3f g = Normalize(target - origin);
        Vector3f gxt = Normalize(Cross(g, up));
        Vector3f t = Cross(gxt, g);
        return Transpose(Rotate(gxt, t, -g)) * Translate(-origin);
    }


    //正交投影变换矩阵
    inline Matrix4f Orthogonal(float aspectRatio, float fov, float n, float f) {
        //参数far和near为远近平面的长度，即正值
        float t = Tan(Radians(fov / 2)) * n;
        float r = t * aspectRatio;

        //直接构建
        return {
                {1 / r, 0,     0,           0},
                {0,     1 / t, 0,           0},
                {0,     0,     2 / (f - n), -(f + n) / (f - n)},
                {0,     0,     0,           1}
        };

        //先位移后缩放
        Vector3f translation(0, 0, -(n + f) / 2);
        Vector3f scale(1 / r, 1 / t, 2 / (f - n));
        return Scale(scale) * Translate(translation);
    }

    //透视转正交矩阵
    inline Matrix4f PerspToOrtho(float n, float f) {
        return {
                {n, 0, 0,        0},
                {0, n, 0,        0},
                {0, 0, -(n + f), -n * f},
                {0, 0, 1,        0}
        };
    }

    //透视投影变换矩阵
    inline Matrix4f Perspective(float aspectRatio, float fov, float n, float f) {
        //参数far和near为远近平面的长度，即正值
        float t = Tan(Radians(fov / 2)) * n;
        float r = t * aspectRatio;

        //直接构建
        return {
                {n / r, 0,     0,                  0},
                {0,     n / t, 0,                  0},
                {0,     0,     -(n + f) / (f - n), -2 * f * n / (f - n)},
                {0,     0,     -1,                 0}
        };

        //先透视转正交再正交投影
        return Orthogonal(aspectRatio, fov, n, f) * PerspToOrtho(n, f);
    }

    //视口变换矩阵
    inline Matrix4f ScreenMapping(const Vector2f &size) {
        return {
                {size.x / 2, 0,          0, size.x / 2},
                {0,          size.y / 2, 0, size.y / 2},
                {0,          0,          1, 0},
                {0,          0,          0, 1}
        };
    }
}