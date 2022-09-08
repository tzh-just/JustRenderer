#pragma once

#include "Global.h"

#include "Color3.h"

namespace Just {

template<typename T>
struct Color4 {
    T r, g, b, a;

    Color4() : r(T()), g(T()), b(T()), a(T()) {}

    explicit Color4(T value) : r(value), g(value), b(value), a(value) {}

    explicit Color4(const Color3<T>& color) : r(color.r), g(color.g), b(color.b), a(1) {}

    Color4(T r, T g, T b) : r(r), g(g), b(b), a(a) {}

    T operator[](size_t i) const {
        assert(i < 4);
        return (&r)[i];
    }

    T& operator[](size_t i) {
        assert(i < 4);
        return (&r)[i];
    }

    bool HasNaNs() const {
        return std::isnan(r) || std::isnan(g) || std::isnan(b) || std::isnan(a);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Color4<T>& c) {
    os << c.r << " " << c.g << " " << c.b;
    return os;
}

using RGBA = Color4<uint8_t>;

}