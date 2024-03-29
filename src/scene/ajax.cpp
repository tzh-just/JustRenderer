
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
    Point3f target(-64.8161, 47.2211, 23.8576);
    Point3f origin(-65.6055, 47.5762, 24.3583);
    Vector3f up(0.299858, 0.934836, -0.190177);
    float fov = 30;
    auto camera = std::make_shared<PerspectiveCamera>(
            Transform(Inverse(LookAt(origin, target, up))),
            film, fov
    );

    //采样器
    int spp = 1;
    auto sampler = std::make_shared<IndependentSampler>(spp);

    //场景构建
    auto ajax_trans = std::make_shared<Transform>(Matrix4x4::Identity());
    auto ajax_mesh = std::make_shared<Mesh>(ajax_trans);
    auto bvh = std::make_shared<BVHAccel>();
    Loader::LoadMesh(ajax_mesh, "scene/ajax/meshes/ajax.obj");
    auto scene = std::make_shared<Scene>(bvh);
    scene->meshes.push_back(ajax_mesh);
    scene->Activate();


    //简单积分器
    {
        sampler->spp = 1;
        auto lightPosition = Point3f(-20, 40, 20);
        auto energy = Spectrum(3.76e4, 3.76e4, 3.76e4);
        auto integrator = std::make_shared<RemappingIntegraor>(camera, sampler, film, lightPosition, energy, RemappingType::Depth);
        integrator->Render(scene, "test/ajax_remapping_depth_test.png");
    }

}