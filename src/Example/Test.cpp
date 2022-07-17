
#include "Just/Math/Vector.h"
#include "Just/Math/Matrix.h"
#include "Just/Graphic/Transform.h"
#include "Just/Geometry/Ray.h"
#include "Just/Geometry/Vertex.h"
#include "Just/Geometry/Triangle.h"
#include "Just/Geometry/Sphere.h"

using namespace Just;

static void TestVector() {
    Vector3f v1(1), v2(2);
    std::cout << "v1 : " << v1 << std::endl;
    std::cout << "v2 : " << v2 << std::endl;
    std::cout << "Length(v1) : " << Length(v1) << std::endl;
    std::cout << "Norm(v1) : " << Norm(v1) << std::endl;
    std::cout << "Dot(v1, v2) : " << Dot(v1, v2) << std::endl;
    std::cout << "Cross(v1, v4) : " << Cross(v1, v2) << std::endl;
    std::cout << "Normalize(v1) : " << Normalize(v1) << std::endl;
    std::cout << "Length(Normalize(v1)) : " << Length(Normalize(v1)) << std::endl;
}

static void TestMatrix() {
    Matrix3f mat1 = {
            {0, 0, 0},
            {2, 2, 0},
            {3, 4, 0}
    };
    std::cout << "mat1 : " << mat1 << std::endl;
    mat1.SetRow(0, {1, 2, 3});
    mat1.SetCol(2, {3, 1, 3});
    std::cout << "mat1.SetRow(0, {1, 2, 3}) : \n" << mat1 << std::endl;
    std::cout << "mat1.SetCol(2, {3, 1, 3}) : \n" << mat1 << std::endl;
    std::cout << "mat1 : " << mat1 << std::endl;
    std::cout << "mat1.Row(0) = " << mat1.Row(0) << std::endl;
    std::cout << "mat1.Col(0) = " << mat1.Col(0) << std::endl;
    std::cout << "Minor(mat1, 1, 1) : \n" << Minor(mat1, 1, 1) << std::endl;
    std::cout << "Cofactor(mat1, 0, 0) : " << Cofactor(mat1, 0, 0) << std::endl;
    std::cout << "Cofactor(mat1, 0, 1) : " << Cofactor(mat1, 0, 1) << std::endl;
    std::cout << "Cofactor(mat1, 0, 2) : " << Cofactor(mat1, 0, 2) << std::endl;
    std::cout << "Det(mat1) : " << Det(mat1) << std::endl;
    std::cout << "Transpose(mat1) : \n" << Transpose(mat1) << std::endl;
    std::cout << "Adjoint(mat1) : \n" << Adjoint(mat1) << std::endl;
    std::cout << "Invert(mat1) : \n" << Invert(mat1) << std::endl;
    Vector3f v1(1, 2, 3);
    std::cout << "v1 : " << v1 << std::endl;
    std::cout << "mat1 * mat1 : \n" << mat1 * mat1 << std::endl;
    std::cout << "mat1 * v1 : " << mat1 * v1 << std::endl;
    std::cout << "v1 * mat1 : " << v1 * mat1 << std::endl;
}

static void TestGeometry() {
    Ray3f ray;
    std::cout << "RAY ray" << std::endl << ray << "\n\n";

    Vertex3f v1({-10, 0, 0});
    Vertex3f v2({10, 0, 0});
    Vertex3f v3({0, 10, 0});
    std::cout << "VERTEX v1" << std::endl << v1 << "\n\n";

    Triangle3f tri(v1, v2, v3);
    std::cout << "TRIANGLE tri" << std::endl << tri << "\n\n";

    HitRecord record;
    std::cout << "RECORD record" << std::endl << record << "\n\n";

    Sphere sphere(10);
    std::cout << "SPHERE sphere" << std::endl << sphere << "\n\n";
}

static void TestMath() {

}

int main() {
    //TestVector();
    //TestMatrix();
    //TestGeometry();
    TestMath();
}
