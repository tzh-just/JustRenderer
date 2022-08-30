
#include <Core/Integrator.h>
#include <Math/Color3.h>

namespace Just {
    void SamplerIntegrator::Render(std::shared_ptr<Scene> scene) {
        Spectrum radiance;
        //#pragma omp parallel for schedule(dynamic, 1) private(radiance)
        for (int y = camera->film->resolution.y; y >= 0; --y) {
            for (int x = camera->film->resolution.x; x >= 0; --x) {

            }
        }
    }
}