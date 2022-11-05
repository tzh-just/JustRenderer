
#include <Global.h>

#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Math/Point2.h"
#include "Math/Color3.h"
#include <Math/Matrix4x4.h>
#include <Math/Transform.h>

#include <Tools/RNG.h>
#include <Tools/Loader.h>

#include <Core/Film.h>
#include <Accel/BVHAccel.h>
#include <Camera/PerspectiveCamera.h>
#include <Integrator/NormalsIntegrator.h>
#include <Integrator/SimpleIntegrator.h>
#include <Integrator/AOIntegrator.h>
#include <Integrator/RemappingIntegrator.h>
#include <Sampler/IndependentSampler.h>
#include <Shape/Sphere.h>

using namespace Just;

int main() {
    //成像平面
    int width = 768;
    int height = 768;
    Point2i resolution(width, height);
    auto film = std::make_shared<Film>(resolution);

    //摄像机
    Point3f target(0.0f, 0.0f, 0.0f);
    Point3f origin(0.0f, 0.0f, 1.0f);
    Vector3f up(0.0f, 1.0f, 0.0f);
    float fov = 45;
    auto camera = std::make_shared<PerspectiveCamera>(
            Transform(Inverse(LookAt(origin, target, up))),
            film, fov
    );

    //采样器
    int spp = 1;
    auto sampler = std::make_shared<IndependentSampler>(spp);

    //场景构建
    auto african_trans = std::make_shared<Transform>(
            Translate(Vector3f(0.0f, 0.0f, -3.0f)) *
            RotateY(30.f)
    );
    auto african_mesh = std::make_shared<Mesh>(african_trans);
    auto bvh = std::make_shared<BVHAccel>();
    Loader::LoadMesh(african_mesh, "scene/african/meshes/african.obj");
    auto scene = std::make_shared<Scene>(bvh);
    scene->meshes.push_back(african_mesh);
    scene->Activate();

/*    //法线积分器
    {
        auto integrator = std::make_shared<NormalsIntegrator>(camera, sampler, film);
        integrator->Render(scene, "test/ajax_normal.png");
    }*/

    //简单积分器
    {
        sampler->spp = 1;
        auto lightPosition = Point3f(1, 0, 0);
        auto energy = Spectrum(100, 100, 100);
        auto integrator = std::make_shared<SimpleIntegrator>(camera, sampler, film, lightPosition, energy);
        integrator->Render(scene, "test/african_simple.png");
    }
/*    //AO积分器
    {
        sampler->spp = 512;
        auto integrator = std::make_shared<AOIntegrator>(camera, sampler, film);
        integrator->Render(scene, "test/ajax_ao.png");
    }*/
}