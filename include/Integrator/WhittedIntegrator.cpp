
#include <Integrator/WhittedIntegrator.h>

namespace Just {

    Spectrum WhittedIntegrator::Li(const Ray& ray) const {
        return {1.0f, 1.0f, 1.0f};
    }
}