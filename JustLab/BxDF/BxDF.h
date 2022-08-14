#pragma once

namespace Just{
    struct BxDF{
        virtual float Pdf() const = 0;
    };
}