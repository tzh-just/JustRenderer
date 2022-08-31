
#include <Integrator/WhittedIntegrator.h>

namespace Just {

    Spectrum WhittedIntegrator::Li(const Ray& ray) const {
        //射线相交测试
        HitRecord record;
        if(!scene->RayIntersect(ray, record)){
            return Spectrum(0.0f);
        }
        return {1.0f, 1.0f, 1.0f};
    }
}