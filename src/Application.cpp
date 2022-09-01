
#include <Global.h>

#include "Math/Vector.h"
#include <Math/Matrix.h>
#include <Math/Transform.h>

#include <Tools/RNG.h>
#include <Tools//Timer.h>
#include <Tools/Loader.h>

#include <Core/Film.h>
#include <Accel/BVH.h>
#include <Light/AreaLight.h>
#include <Camera/PerspectiveCamera.h>
#include <Integrator/WhittedIntegrator.h>
#include <Sampler/TrapezoidalSampler.h>

using namespace Just;

int main() {
    //TestVector();
    //TestMatrix();
    //TestTransform();
    //TestRandom();
    //TestLoadMesh();
    //TestLoadTexture();

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
    Loader::LoadMesh(cboxFloorMesh, "scene/CornellBox/Mesh/Floor");
    auto cboxCeilingMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxCeilingMesh, "scene/CornellBox/Mesh/Ceiling");
    auto cboxBackWallMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxBackWallMesh, "scene/CornellBox/Mesh/BackWall");
    auto cboxRightWallMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxRightWallMesh, "scene/CornellBox/Mesh/RightWall");
    auto cboxLeftWallMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxLeftWallMesh, "scene/CornellBox/Mesh/LeftWall");
    auto cboxLightMesh = std::make_shared<Mesh>();
    Loader::LoadMesh(cboxLightMesh, "scene/CornellBox/Mesh/Light");

    scene->meshes.push_back(cboxFloorMesh);
    scene->meshes.push_back(cboxCeilingMesh);
    scene->meshes.push_back(cboxBackWallMesh);
    scene->meshes.push_back(cboxRightWallMesh);
    scene->meshes.push_back(cboxLeftWallMesh);
    scene->meshes.push_back(cboxLightMesh);

    //光源
    auto light = std::make_shared<AreaLight>();
    scene->lights.push_back(light);

    //渲染
    integrator->Render(scene);
}

static void TestVector() {
    Vector3f v1(2, 0, 0), v2(0, 2, 0);
    Print(
            "v1", v1,
            "v2", v2,
            "Length(v1) = ", v1.Length(),
            "Dot(v1, v2)", Dot(v1, v2),
            "Cross(v1, v2) = ", Cross(v1, v2),
            "Normalize(v1) = ", Normalize(v1),
            "Normalize(v1).Length() = ", Normalize(v1).Length()
    );
}

static void TestMatrix() {
    Matrix3f mat1 = {
            {1, 2, 3},
            {2, 2, 1},
            {3, 4, 3}
    };
    Vector3f v1(1, 2, 3);
    Print(
            "mat1 = ", mat1,
            "Minor(1, 1) = ", mat1.Minor(1, 1),
            "Cofactor(0, 0) = ", mat1.Cofactor(0, 0),
            "Cofactor(0, 1) = ", mat1.Cofactor(0, 1),
            "Cofactor(0, 2) = ", mat1.Cofactor(0, 2),
            "Det() = ", mat1.Det(),
            "Transpose(mat1) = ", Transpose(mat1),
            "Adjoint(mat1) = ", Adjoint(mat1),
            "Invert(mat1) = ", Invert(mat1),
            "v1 = ", v1,
            "mat1 * mat1 = ", mat1 * mat1,
            "mat1 * v1 = ", mat1 * v1
    );
}

static void TestTransform() {
    Point4f p(1, 0, 0, 1);

    auto M = RotateZ(90);
    auto r = M * p;

    auto T = Translate(0, 1, 0);
    auto t = T * r;

    Print(
            "p = ", p,
            "M = ", M,
            "r = M * p", r,
            "T = ", T,
            "t = T * r", t
    );
}

static void TestRandom() {
    //随机数性能测试
    RNG rng;
    Timer timer;
    timer.Begin();
    Print(
            rng.UniformFloat(),
            rng.UniformFloat(),
            rng.UniformFloat(),
            rng.UniformFloat(),
            rng.UniformFloat(),
            rng.UniformFloat(),
            rng.UniformFloat(),
            rng.UniformFloat(),
            rng.UniformFloat(),
            rng.UniformFloat()
    );
    timer.End();
    Print(timer.time);
}

static void TestLoadMesh() {
    auto mesh = std::make_shared<Mesh>();
    Loader::LoadMesh(mesh, "Scene/CornellBox/Mesh/TallBlock.obj");
}

static void TestLoadTexture() {
    auto texture = std::make_shared<Texture>();
    Loader::LoadTexture(texture, "Scene/AfricanHead/Texture/Diffuse.tga");
}