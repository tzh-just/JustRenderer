
#include <Global.h>

#include "Math/Vector.h"
#include <Math/Matrix.h>
#include <Math/Transform.h>

#include <Tools/RNG.h>
#include <Tools//Timer.h>
#include <Tools/Loader.h>

static void TestVector();

static void TestMatrix();

static void TestTransform();

using namespace Just;

int main() {

    TestVector();
    TestMatrix();
    //TestTransform();
    //TestRandom();
    //TestLoadMesh();
    //TestLoadTexture();
}

static void TestVector() {
    Vector3f v1(2, 0, 0), v2(0, 2, 0);
    std::cout << "v1 = " << v1 << "\n";
    std::cout << "v1 = " << v2 << "\n";
    std::cout << "Length(v1) = " << Length(v1) << "\n";
    std::cout << "Dot(v1, v2) = " << Dot(v1, v2) << "\n";
    std::cout << "Cross(v1, v2) = " << Cross(v1, v2) << "\n";
    std::cout << "Normalize(v1) = " << Normalize(v1) << "\n";
    std::cout << "Normalize(v1).Length() = " << Length(Normalize(v1)) << "\n";
}

static void TestMatrix() {
    Matrix3f mat1 = {
            {1, 2, 3},
            {2, 2, 1},
            {3, 4, 3}
    };
    Vector3f v1(1, 2, 3);
    std::cout << "mat1 = " << mat1 << "\n";
    std::cout << "Minor(1, 1) = " << Minor(mat1, 1, 1) << "\n";
    std::cout << "Cofactor(0, 0) = " << Cofactor(mat1, 0, 0) << "\n";
    std::cout << "Cofactor(0, 1) = " << Cofactor(mat1, 0, 1) << "\n";
    std::cout << "Cofactor(0, 2) = " << Cofactor(mat1, 0, 2) << "\n";
    std::cout << "Det() = " << Det(mat1) << "\n";
    std::cout << "Transpose(mat1) = " << Transpose(mat1) << "\n";
    std::cout << "Adjoint(mat1) = " << Adjoint(mat1) << "\n";
    std::cout << "Invert(mat1) = " << Invert(mat1) << "\n";
    std::cout << "v1 = " << v1 << "\n";
    std::cout << "mat1 * mat1 = " << mat1 * mat1 << "\n";
    std::cout << "mat1 * v1 = " << mat1 * v1 << "\n";
}

static void TestTransform() {
    Point4f p(1, 0, 0, 1);

    auto M = Transform::RotateZ(90);
    auto r = M * p;

    auto T = Transform::Translate(0, 1, 0);
    auto t = T * r;

    std::cout << "p = " << p << "\n";
    std::cout << "M = " << M << "\n";
    std::cout << "r = M * p =" << r << "\n";
    std::cout << "T = " << T << "\n";
    std::cout << "t = T * r = " << t << "\n";
}

static void TestLoadMesh() {
    auto mesh = std::make_shared<Mesh>();
    Loader::LoadMesh(mesh, "Scene/CornellBox/Mesh/TallBlock.obj");
}

static void TestLoadTexture() {
    auto texture = std::make_shared<Texture>();
    Loader::LoadTexture(texture, "Scene/AfricanHead/Texture/Diffuse.tga");
}



