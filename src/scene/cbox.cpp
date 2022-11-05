
#include <Global.h>

#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Math/Point2.h"
#include "Integrator/SimpleIntegrator.h"
#include <Math/Matrix4x4.h>
#include <Math/Transform.h>

#include <Tools/RNG.h>
#include <Tools/Loader.h>

#include <Core/Film.h>
#include <Accel/BVHAccel.h>
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
    Point3f origin(278, 273, -800);
    Point3f target(278, 273, -799);
    Vector3f up(0, 1, 0);
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

    auto bvh = std::make_shared<BVHAccel>();

    auto mesh_back = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(mesh_back, "scene/cbox/meshes/cbox_back.obj");
    auto mesh_ceiling = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(mesh_ceiling, "scene/cbox/meshes/cbox_ceiling.obj");
    auto mesh_floor = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(mesh_floor, "scene/cbox/meshes/cbox_floor.obj");
    auto mesh_greenwall = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(mesh_greenwall, "scene/cbox/meshes/cbox_greenwall.obj");
    auto mesh_redwall = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(mesh_redwall, "scene/cbox/meshes/cbox_redwall.obj");
    auto mesh_smallbox = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(mesh_smallbox, "scene/cbox/meshes/cbox_smallbox.obj");
    auto mesh_largebox = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(mesh_largebox, "scene/cbox/meshes/cbox_largebox.obj");
    auto mesh_luminaire = std::make_shared<Mesh>(trans);
    Loader::LoadMesh(mesh_luminaire, "scene/cbox/meshes/cbox_luminaire.obj");

    auto scene = std::make_shared<Scene>(bvh);
    scene->meshes.push_back(mesh_back);
    scene->meshes.push_back(mesh_ceiling);
    scene->meshes.push_back(mesh_floor);
    scene->meshes.push_back(mesh_greenwall);
    scene->meshes.push_back(mesh_redwall);
    scene->meshes.push_back(mesh_smallbox);
    scene->meshes.push_back(mesh_largebox);
    scene->meshes.push_back(mesh_luminaire);
    scene->Activate();
    //积分器
    auto integrator = std::make_shared<NormalsIntegrator>(camera, sampler, film);
    integrator->Render(scene, "test/cbox_normal.tga");
}