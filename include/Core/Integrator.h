#pragma once

#include "Global.h"
#include "Math/Vector.h"
#include "Geometry/Ray.h"
#include "Scene.h"
#include "Sampler.h"
#include "Camera.h"

namespace Just {
    struct Integrator {
        virtual void Render() = 0;
    };

    struct SamplerIntegrator : public Integrator {
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Sampler> sampler;
        std::shared_ptr<Film> film;
        std::shared_ptr<Scene> scene;

        SamplerIntegrator(std::shared_ptr<Camera> camera,
                          std::shared_ptr<Sampler> sampler,
                          std::shared_ptr<Film> film,
                          std::shared_ptr<Scene> scene)
                : camera(camera), sampler(sampler), film(film), scene(scene) {}

        virtual Spectrum Li(const Ray3f& ray) const = 0;

        void Render() override;
    };
void SamplerIntegrator::Render() {

    Spectrum radiance;

    //#pragma omp parallel for schedule(dynamic, 1) private(radiance)

    for (int y = film->resolution.y; y >= 0; --y) {

        for (int x = 0; x < film->resolution.x; ++x) {

            std::cout << 100.0 * (film->resolution.y - 1 - y) / (film->resolution.y - 1)
                      << "%" << std::endl;

            radiance = Spectrum(0.0f);

            for (int i = 0; i < sampler->spp; ++i) {
                //计算光线投射点
                auto [sx, sy] = sampler->Sample(float(x), float(y));
                float s = sx / float(film->resolution.x - 1);
                float t = sy / float(film->resolution.y - 1);
                //投射光线并累计颜色
                radiance += Li(camera->CastRay(s, t));
            }

            //计算像素索引
            int pixelIndex = (film->resolution.y - 1 - y) * (film->resolution.x - 1) + x;
            radiance /= sampler->spp;
            film->pixels[pixelIndex] = Pixel(Spectrum2RGB(radiance));
        }
    }

    //保存渲染结果
    film->StoreImage();
}
}