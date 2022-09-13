
#include <Global.h>

#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Math/Point2.h"
#include <Math/Matrix4x4.h>
#include <Math/Transform.h>

#include <Tools/RNG.h>
#include <Tools/Loader.h>

#include <Core/Film.h>
#include <Accel/BVH.h>
#include <Camera/PerspectiveCamera.h>
#include <Integrator/NormalsIntegrator.h>
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
    Point3f origin(-0.0315182, 0.284011, 0.7331);
    Point3f target(-0.0123771, 0.0540913, -0.239922);
    Vector3f up(0.00717446, 0.973206, -0.229822);
    float fov = 16;
    auto camera = std::make_shared<PerspectiveCamera>(
            Transform(Inverse(LookAt(origin, target, up))),
            film, fov
    );

    //采样器
    int spp = 1;
    auto sampler = std::make_shared<IndependentSampler>(spp);

    //场景构建
    auto bunnyTrans = std::make_shared<Transform>(Matrix4x4::Identity());
    auto bunnyMesh = std::make_shared<Mesh>(bunnyTrans);
    auto bvh = std::make_shared<BVH>();
    Loader::LoadMesh(bunnyMesh, "scene/bunny/meshes/bunny.obj");
    auto scene = std::make_shared<Scene>(bvh);
    scene->meshes.push_back(bunnyMesh);
    scene->Activate();

    //积分器
    auto integrator = std::make_shared<NormalsIntegrator>(camera, sampler, film);
    integrator->Render(scene, "test/bunny_normal.tga");
}