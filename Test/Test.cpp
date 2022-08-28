
#include <Global.h>
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Point2.h"
#include "Math/Point3.h"
#include "Math/Point4.h"
#include "Math/Matrix4.h"
#include "Geometry/Transform.h"
#include "Tools/RNG.h"
#include "Tools//Timer.h"
#include "Tools/Loader.h"

using namespace Just;

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

void TestRandom() {
    //随机数性能测试
    RNG rng;
    Timer timer;
    timer.Begin();
    Print(
            rng.Random(),
            rng.Random(),
            rng.Random(),
            rng.Random(),
            rng.Random(),
            rng.Random(),
            rng.Random(),
            rng.Random(),
            rng.Random(),
            rng.Random()
    );
    timer.End();
    Print(timer.time);
}

static void TestLoader() {
    auto mesh = new TriangleMesh();
    Loader::LoadMesh(mesh, "Scene/cbox/meshes/TallBlock.obj");
    std::cout << mesh->positions.size() << "\n";
}


int main() {
    //TestVector();
    //TestMatrix();
    //TestTransform();
    //TestRandom();
    TestLoader();
}
