#pragma once

#include <cstdint>

namespace Just{
    struct BxDF{
        virtual float Pdf() const = 0;
    };
}