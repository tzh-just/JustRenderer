#pragma once

#include "Global.h"
#include "Math/Vector3.h"
#include "Geometry/Ray.h"
#include "Scene.h"
#include "Sampler.h"
#include "Camera.h"
#include "omp.h"
#include "Tools/Timer.h"

namespace Just {
struct Integrator {
    virtual void Render(std::shared_ptr<Scene> scene, const std::string& filename) = 0;
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

    void Render(std::shared_ptr<Scene> scene, const std::string& filename) override;
};

void SamplerIntegrator::Render(std::shared_ptr<Scene> scene, const std::string& filename) {
    Spectrum radiance(0.0f);
    film->frameBuffer = std::vector<RGB>(film->resolution.x * film->resolution.y, RGB(0.0f));

    //计时器
    Timer timer;
    timer.Begin();

    //OpenMP多线程渲染
#pragma omp parallel for schedule(dynamic) private(radiance)
    for (int y = 0; y < film->resolution.y; ++y) {
        //printf("\r%f\n", 100.0f * float(y) / float(film->resolution.y - 1));
        for (int x = 0; x < film->resolution.x; ++x) {
            radiance.Clear();
            for (int i = 0; i < sampler->spp; ++i) {
                //投射光线并累计颜色
                Ray ray = camera->GenerateRay(Point2f(float(x), float(y)));
                radiance += Li(ray, scene);
            }
            radiance /= sampler->spp;
            film->frameBuffer[y * film->resolution.x + x] = ToSRGB(radiance);
        }
    }

    timer.End();
    std::cout << "[Render time]: " << timer.time << "ms" << std::endl;
    //保存渲染结果
    film->StoreImage(filename, ImageType::PNG);
}
}