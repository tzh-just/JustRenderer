//================================================
// 渲染器
//================================================

#pragma once

namespace Just {
    class Renderer {
    public:
        virtual void Render() = 0;
    };

    class Rasterizer : public Renderer {
    public:
        void Render() override {}
    };

    class RayTracer : public Renderer {
    public:
        void Render() override {}
    };
}