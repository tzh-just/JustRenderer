
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
#include <Accel/BVH.h>
#include <Accel/Naive.h>
#include <Light/AreaLight.h>
#include <Camera/PerspectiveCamera.h>
#include <Integrator/WhittedIntegrator.h>
#include <Sampler/TrapezoidalSampler.h>
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
    Loader::LoadMesh(bunnyMesh, "scene/Bunny/Mesh/bunny.obj");
    auto scene = std::make_shared<Scene>(bvh);
    scene->meshes.push_back(bunnyMesh);
    scene->Activate();

    //积分器
    auto integrator = std::make_shared<WhittedIntegrator>(camera, sampler, film);
    integrator->Render(scene, "test/output1.tga");

    //模型
/*    auto cboxFloorMesh = std::make_shared<Mesh>(transform);
    Loader::LoadMesh(cboxFloorMesh, "scene/CornellBox/Mesh/Floor.obj", toWorld);
    auto cboxCeilingMesh = std::make_shared<Mesh>(transform);
    Loader::LoadMesh(cboxCeilingMesh, "scene/CornellBox/Mesh/Ceiling.obj", toWorld);
    auto cboxBackWallMesh = std::make_shared<Mesh>(transform);
    Loader::LoadMesh(cboxBackWallMesh, "scene/CornellBox/Mesh/BackWall.obj", toWorld);
    auto cboxRightWallMesh = std::make_shared<Mesh>(transform);
    Loader::LoadMesh(cboxRightWallMesh, "scene/CornellBox/Mesh/RightWall.obj", toWorld);
    auto cboxLeftWallMesh = std::make_shared<Mesh>(transform);
    Loader::LoadMesh(cboxLeftWallMesh, "scene/CornellBox/Mesh/LeftWall.obj", toWorld);
    auto cboxLightMesh = std::make_shared<Mesh>(transform);
    Loader::LoadMesh(cboxLightMesh, "scene/CornellBox/Mesh/Light.obj", toWorld);

    scene->meshes.push_back(cboxFloorMesh);
    scene->meshes.push_back(cboxCeilingMesh);
    scene->meshes.push_back(cboxBackWallMesh);
    scene->meshes.push_back(cboxRightWallMesh);
    scene->meshes.push_back(cboxLeftWallMesh);
    scene->meshes.push_back(cboxLightMesh);*/
}