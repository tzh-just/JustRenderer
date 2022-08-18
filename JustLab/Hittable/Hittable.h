#pragma once

namespace Just{
    struct Hittable{
        virtual bool Intersect() const = 0;
    };
}