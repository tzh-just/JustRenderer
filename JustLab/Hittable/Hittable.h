//================================================
// 射线与几何体相交信息
//================================================

#pragma once

namespace Just{
    struct Hittable{
        virtual bool Intersect() const = 0;
    };
}