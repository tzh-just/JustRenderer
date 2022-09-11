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

    Spectrum radiance(0.0f);
    film->frameBuffer = std::vector<RGB>(film->resolution.x * film->resolution.y, RGB(0.0f));
#pragma omp parallel for schedule(dynamic, 1) private(radiance)
    for (int y = 0; y < film->resolution.y; ++y) {
        for (int x = 0; x < film->resolution.x; ++x) {
            std::cout << 100.0f * float(y) / float(film->resolution.y - 1)
                      << "%" << std::endl;
            radiance.Clear();
            for (int i = 0; i < sampler->spp; ++i) {
                //投射光线并累计颜色
                Ray ray = camera->GenerateRay(Point2f(float(x), float(y)));
                radiance += Li(ray, scene);
            }
            radiance /= sampler->spp;
            film->frameBuffer[y * film->resolution.x + x] = ToRGB(radiance);
        }
    }

    //保存渲染结果
    film->StoreImage("test/output1.tga", ImageType::TGA);
}
}