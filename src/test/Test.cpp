
#include <Global.h>

#include <Math/Vector3.h>
#include <Math/Matrix4x4.h>
#include <Math/Transform.h>

#include <Tools/RNG.h>
#include <Tools//Timer.h>
#include <Tools/Loader.h>
#include <Math/Matrix4x4.h>

static void TestVector();

static void TestMatrix();

using namespace Just;

int main() {
    TestVector();
    TestMatrix();
}

static void TestVector() {
    Vector3f v1(2, 0, 0), v2(0, 2, 0);
    std::cout << "v1 = " << v1 << "\n";
    std::cout << "v1 = " << v2 << "\n";
    std::cout << "Length(v1) = " << v1.Length() << "\n";
    std::cout << "Dot(v1, v2) = " << Dot(v1, v2) << "\n";
    std::cout << "Cross(v1, v2) = " << Cross(v1, v2) << "\n";
    std::cout << "Normalize(v1) = " << Normalize(v1) << "\n";
    std::cout << "Normalize(v1).Length() = " << Normalize(v1).Length() << "\n";
}

static void TestMatrix() {
    Matrix4x4 mat(
            1, 0, 0, 3,
            0, 2, 0, 0,
            1, 0, 3, 0,
            0, 4, 0, 4
    );

    auto adjoint = Adjoint(mat);
    auto inverse = Inverse(mat);
    auto transpose = Transpose(adjoint);
}