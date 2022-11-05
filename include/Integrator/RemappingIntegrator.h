#pragma once

#include "Core/Integrator.h"
#include "Math/Point3.h"
#include "Math/Color3.h"
#include "Tools/Warp.h"

namespace Just {
enum class RemappingType {
    Radiance,
    NdotL,
};

struct RemappingIntegraor : public SamplerIntegrator {
    Point3f position;
    Spectrum energy;
    RemappingType type;
    Transform cameraToScreen;

    RemappingIntegraor(std::shared_ptr<Camera> camera, std::shared_ptr<Sampler> sampler, std::shared_ptr<Film> film,
                       const Point3f& position, const Spectrum& energy, RemappingType type)
            : SamplerIntegrator(camera, sampler, film), position(position), energy(energy), type(type) {
        cameraToScreen = dynamic_cast<ProjectiveCamera*>(camera.get())->cameraToScreen;
    }

    Spectrum Li(const Ray& ray, std::shared_ptr<Scene> scene) const override;

    static Spectrum Remapping(float weight);
};

Spectrum RemappingIntegraor::Remapping(float weight) {
    if (weight < 0.25f) return {0.1f, 0.1f, 0.85f}; // blue
    if (weight < 0.5f) return {0.1f, 0.85f, 0.1f}; // green
    if (weight < 0.75f) return {0.85f, 0.85f, 0.1f}; // yellow
    return {0.85f, 0.1f, 0.1f}; // red
}


Spectrum RemappingIntegraor::Li(const Ray& ray, std::shared_ptr<Scene> scene) const {
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
    auto radiance = 0.25f * kInvPI * kInvPI * energy * cosTheta / L.LengthSquared();

    if (type == RemappingType::Radiance) {
        return Remapping(radiance.Luminance());
    } else if (type == RemappingType::NdotL) {
        return Remapping(cosTheta);
    }
}
}//namespace