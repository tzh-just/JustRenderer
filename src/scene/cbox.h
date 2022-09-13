
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
    auto trans = std::make_shared<Transform>(Matrix4x4::Identity());
    
    auto bvh = std::make_shared<BVH>();
    
    auto cboxFloorMesh = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(cboxFloorMesh, "scene/CornellBox/Mesh/Floor.obj");
    auto cboxCeilingMesh = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(cboxCeilingMesh, "scene/CornellBox/Mesh/Ceiling.obj");
    auto cboxBackWallMesh = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(cboxBackWallMesh, "scene/CornellBox/Mesh/BackWall.obj");
    auto cboxRightWallMesh = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(cboxRightWallMesh, "scene/CornellBox/Mesh/RightWall.obj");
    auto cboxLeftWallMesh = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(cboxLeftWallMesh, "scene/CornellBox/Mesh/LeftWall.obj");
    auto cboxLightMesh = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(cboxLightMesh, "scene/CornellBox/Mesh/Light.obj");
    
    auto scene = std::make_shared<Scene>(bvh);
    scene->meshes.push_back(cboxFloorMesh);
    scene->meshes.push_back(cboxCeilingMesh);
    scene->meshes.push_back(cboxBackWallMesh);
    scene->meshes.push_back(cboxRightWallMesh);
    scene->meshes.push_back(cboxLeftWallMesh);
    scene->meshes.push_back(cboxLightMesh);
    scene->Activate();
    //积分器
    auto integrator = std::make_shared<NormalsIntegrator>(camera, sampler, film);
    integrator->Render(scene, "test/bunny_normal.tga");
}