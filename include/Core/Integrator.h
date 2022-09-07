#pragma once

#include "Global.h"
#include "Math/Vector3.h"
#include "Geometry/Ray.h"
#include "Scene.h"
#include "Sampler.h"
#include "Camera.h"

namespace Just {
struct Integrator {
    virtual void Render(std::shared_ptr<Scene> scene) = 0;
};

struct SamplerIntegrator : public Integrator {
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Sampler> sampler;
    std::shared_ptr<Film> film;

    SamplerIntegrator(std::shared_ptr<Camera> camera,
                      std::shared_ptr<Sampler> sampler,
                      std::shared_ptr<Film> film)
            : camera(camera), sampler(sampler), film(film) {}

    virtual Spectrum Li(const Ray& ray, std::shared_ptr<Scene> scene) const = 0;

    void Render(std::shared_ptr<Scene> scene) override;
};

void SamplerIntegrator::Render(std::shared_ptr<Scene> scene) {

    Spectrum radiance;

    //#pragma omp parallel for schedule(dynamic, 1) private(radiance)

    for (int y = film->resolution.y - 1; y >= 0; --y) {

        for (int x = 0; x < film->resolution.x; ++x) {

            std::cout << 100.0 * (film->resolution.y - 1 - y) / (film->resolution.y - 1)
                      << "%" << std::endl;

            radiance = Spectrum(0.0f);
            for (int i = 0; i < sampler->spp; ++i) {
                //计算光线投射点
                auto [sx, sy] = sampler->Sample(float(x), float(y));
                float s = sx / float(film->resolution.x);
                float t = sy / float(film->resolution.y);
                //投射光线并累计颜色
                Ray ray;
                camera->GenerateRay(Point2f(s, t), ray);
                radiance += Li(ray, scene);
            }
            radiance /= sampler->spp;
            film->pixels.push_back(ToRGB(radiance));
        }
    }

    //保存渲染结果
    film->StoreImage("out.tga");
}
}