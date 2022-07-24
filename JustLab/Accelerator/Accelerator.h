//================================================
// 空间加速结构
//================================================

#pragma once

#include <utility>
#include "Geometry/Hittable.h"

namespace Just {
    class Accelerator : Hittable {
    public:
        virtual void Build() const = 0;

    private:
        virtual void Add() const = 0;
    };
}