#pragma once

namespace Just {
    struct BxDFRecord {

    };
    struct BxDF {
        virtual float Pdf() const = 0;
    };
}