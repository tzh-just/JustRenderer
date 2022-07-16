#pragma once

namespace Just{
    struct HitRecord{

    };

    struct IHitable{
        virtual HitRecord Intersect() = 0;
    };
}