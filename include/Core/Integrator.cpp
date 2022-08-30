
#include <Core/Integrator.h>
#include <Math/Color3.h>

namespace Just {
    void SamplerIntegrator::Render(std::shared_ptr<Scene> scene) {

        Spectrum radiance;

        //#pragma omp parallel for schedule(dynamic, 1) private(radiance)

        for (int y = film->resolution.y; y >= 0; --y) {

            for (int x = 0; x < film->resolution.x; ++x) {

                std::cout << 100.0 * (film->resolution.y - 1 - y) / (film->resolution.y - 1)
                          << "%" << std::endl;

                radiance = Spectrum(0.0f);

                for (int index = 0; index < sampler->spp; ++index) {

                    auto [sx, sy] = sampler->Sample(float(x), float(y));
                    float s = sx / float(film->resolution.x - 1);
                    float t = sy / float(film->resolution.y - 1);
                    //投射光线并累计颜色
                    Ray ray = camera->CastRay(s, t);
                    radiance += Li(ray);
                }
                //计算像素索引
                int pixelIndex = (film->resolution.y - 1 - y) * (film->resolution.x - 1) + x;
                radiance /= static_cast<float>(sampler->spp);
                film->pixels[pixelIndex] = Pixel(Spectrum2RGB(radiance));
            }
        }

        //保存渲染结果
        film->StoreImage();
    }
}