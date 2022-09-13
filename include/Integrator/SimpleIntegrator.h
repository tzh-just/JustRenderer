#pragma once

#include "Core/Integrator.h"
#include "Math/Point3.h"
#include "Math/Color3.h"

namespace Just {
struct SimpleIntegrator : public SamplerIntegrator {
    Point3f position;
    Spectrum energy;

    SimpleIntegrator(std::shared_ptr<Camera> camera, std::shared_ptr<Sampler> sampler, std::shared_ptr<Film> film,
                     const Point3f& position, const Spectrum& energy)
            : SamplerIntegrator(camera, sampler, film), position(position), energy(energy) {}

    Spectrum Li(const Ray& ray, std::shared_ptr<Scene> scene) const override;
};

Spectrum SimpleIntegrator::Li(const Ray& ray, std::shared_ptr<Scene> scene) const {
    //射线相交测试
    HitRecord record;
    if (!scene->RayIntersect(ray, record)) {
        return Spectrum(0.0f);
    }

    Vector3f L = position - record.point;//光源方向

    if (scene->RayIntersect(Ray(record.point + L * kEpsilon, L))) {
        return Spectrum(0.0f);
    }
    //直接光照：Phi/(4*pi*pi) * cos_theta/||x-p||^2 * V(x<->p)

    auto cosTheta = std::max(0.0f, Dot(record.shadingFrame.n, (Normalize(L))));
    return 0.25f * kInvPI * kInvPI * energy * cosTheta / L.LengthSquared();

}
}