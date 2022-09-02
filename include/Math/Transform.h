#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Math.h"

namespace Just {

struct Transform {
    //旋转变换
    static Matrix4f RotateX(float angle) {
        Vector3f v = {1, 2, 3};
        return {
                {1, 0,                        0,                         0},
                {0, std::cos(Radians(angle)), -std::sin(Radians(angle)), 0},
                {0, std::sin(Radians(angle)), std::cos(Radians(angle)),  0},
                {0, 0,                        0,                         1}
        };
    }

    static Matrix4f RotateY(float angle) {
        return {
                {std::cos(Radians(angle)),  0, std::sin(Radians(angle)), 0},
                {0,                         1, 0,                        0},
                {-std::sin(Radians(angle)), 0, std::cos(Radians(angle)), 0},
                {0,                         0, 0,                        1}
        };
    }

    static Matrix4f RotateZ(float angle) {
        return {
                {std::cos(Radians(angle)), -std::sin(Radians(angle)), 0, 0},
                {std::sin(Radians(angle)), std::cos(Radians(angle)),  0, 0},
                {0,                        0,                         1, 0},
                {0,                        0,                         0, 1}
        };
    }

    //旋转变换
    static Matrix4f Rotate(float x, float y, float z) {
        return RotateZ(z) * RotateY(y) * RotateX(x);
    }

    static Matrix4f Rotate(const Vector3f& rotation) {
        return RotateZ(rotation.z) * RotateY(rotation.y) * RotateX(rotation.x);
    }

    static Matrix4f Rotate(const Vector3f& i, const Vector3f& j, const Vector3f& k) {
        return {
                {i.x, j.x, k.x, 0},
                {i.y, j.y, k.y, 0},
                {i.z, j.z, k.z, 0},
                {0,   0,   0,   1}
        };
    }

    //缩放变换
    static Matrix4f Scale(float x, float y, float z) {
        return {
                {x, 0, 0, 0},
                {0, y, 0, 0},
                {0, 0, z, 0},
                {0, 0, 0, 1}
        };
    }

    static Matrix4f Scale(const Vector3f& scale) {

        return {
                {scale.x, 0,       0,       0},
                {0,       scale.y, 0,       0},
                {0,       0,       scale.z, 0},
                {0,       0,       0,       1}
        };
    }

    //平移变换
    static Matrix4f Translate(float x, float y, float z) {
        return {
                {1, 0, 0, x},
                {0, 1, 0, y},
                {0, 0, 1, z},
                {0, 0, 0, 1}
        };
    }

    static Matrix4f Translate(const Point3f& position) {
        return {
                {1, 0, 0, position.x},
                {0, 1, 0, position.y},
                {0, 0, 1, position.z},
                {0, 0, 0, 1}
        };
    }

    //视图变换
    static Matrix4f LookAt(const Point3f& origin, const Point3f& target, const Vector3f& up) {
        Vector3f g = Normalize(target - origin);
        Vector3f gxt = Normalize(Cross(g, up));
        Vector3f t = Cross(gxt, g);
        return Transpose(Rotate(gxt, t, -g)) * Translate(-origin);
    }

    //正交投影变换
    static Matrix4f Orthogonal(float aspectRatio, float fov, float n, float f) {
        //参数far和near为远近平面的长度，即正值
        float t = std::tan(Radians(fov / 2)) * n;
        float r = t * aspectRatio;

        //直接构建
        return {
                {1 / r, 0,     0,           0},
                {0,     1 / t, 0,           0},
                {0,     0,     2 / (f - n), -(f + n) / (f - n)},
                {0,     0,     0,           1}
        };
    }

    //透视投影变换
    static Matrix4f Perspective(float aspectRatio, float fov, float n, float f) {
        //参数far和near为远近平面的长度，即正值
        float t = std::tan(Radians(fov / 2)) * n;
        float r = t * aspectRatio;

        //直接构建
        return {
                {n / r, 0,     0,                  0},
                {0,     n / t, 0,                  0},
                {0,     0,     -(n + f) / (f - n), -2 * f * n / (f - n)},
                {0,     0,     -1,                 0}
        };
    }

    //视口变换
    static Matrix4f ScreenMapping(const Point2f& size) {
        return {
                {size.x / 2, 0,          0, size.x / 2},
                {0,          size.y / 2, 0, size.y / 2},
                {0,          0,          1, 0},
                {0,          0,          0, 1}
        };
    }
};


}