
#include <Global.h>

#include "Math/Vector.h"
#include <Math/Matrix.h>
#include <Math/Transform.h>

#include <Tools/RNG.h>
#include <Tools/Loader.h>

#include <Core/Film.h>
#include <Accel/BVH.h>
#include <Light/AreaLight.h>
#include <Camera/PerspectiveCamera.h>
#include <Integrator/WhittedIntegrator.h>
#include <Sampler/TrapezoidalSampler.h>

using namespace Just;

int main() {
    //屏幕分辨率
    int width = 1024;
    int height = 1024;
    Point2i resolution(width, height);

    //采样数
    int spp = 12;

    //摄像机参数
    Point3f origin(278, 273, -800);
    Point3f target(278, 273, -799);
    Vector3f up(0, 1, 0);
    float aspectRatio = 1;
    float fov = 45;
    float near = 0.035;
    float far = 50;

    //胶片
    auto film = std::make_shared<Film>(resolution);

    //摄像机
    auto camera = std::make_shared<PerspectiveCamera>(origin, target, up, near, far, aspectRatio, fov);

    //采样器
    auto sampler = std::make_shared<TrapezoidalSampler>(spp);

    //积分器
    auto integrator = std::make_shared<WhittedIntegrator>(camera, sampler, film);

    //加速结构
    auto bvh = std::make_shared<BVH>();

    //场景
    auto scene = std::make_shared<Scene>(bvh);

    //模型
    auto cboxFloorMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxFloorMesh, "scene/CornellBox/Mesh/Floor.obj");
    auto cboxCeilingMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxCeilingMesh, "scene/CornellBox/Mesh/Ceiling.obj");
    auto cboxBackWallMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxBackWallMesh, "scene/CornellBox/Mesh/BackWall.obj");
    auto cboxRightWallMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxRightWallMesh, "scene/CornellBox/Mesh/RightWall.obj");
    auto cboxLeftWallMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxLeftWallMesh, "scene/CornellBox/Mesh/LeftWall.obj");
    auto cboxLightMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxLightMesh, "scene/CornellBox/Mesh/Light.obj");

    scene->meshes.push_back(cboxFloorMesh);
    scene->meshes.push_back(cboxCeilingMesh);
    scene->meshes.push_back(cboxBackWallMesh);
    scene->meshes.push_back(cboxRightWallMesh);
    scene->meshes.push_back(cboxLeftWallMesh);
    scene->meshes.push_back(cboxLightMesh);

    scene->Activate();

    //光源
    auto light = std::make_shared<AreaLight>();
    scene->lights.push_back(light);

    //渲染
    integrator->Render();
}