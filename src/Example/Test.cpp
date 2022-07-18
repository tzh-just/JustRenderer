
#include "Just/Vector.h"
#include "Just/Matrix.h"
#include "Just/Ray.h"
#include "Just/Vertex.h"
#include "Just/Triangle.h"
#include "Just/Sphere.h"

using namespace Just;

static void TestVector() {
    Vector3f v1(1), v2(2);
    Print(
            "v1", v1,
            "v2", v2,
            "Length(v1) : ", Length(v1),
            "Norm(v1) : ", Norm(v1),
            "Dot(v1, v2)", Dot(v1, v2),
            "Cross(v1, v2) : ", Cross(v1, v2),
            "Normalize(v1) : ", Normalize(v1),
            "Length(Normalize(v1)) : ", Length(Normalize(v1))
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
            "mat1 : ", mat1,
            "mat1.SetRow(0, {1, 2, 3}) : ", mat1,
            "mat1.SetCol(2, {3, 1, 3}) : ", mat1,
            "mat1 : ", mat1,
            "mat1.Row(0) : ", mat1.Row(0),
            "mat1.Col(0) : ", mat1.Col(0),
            "Minor(mat1, 1, 1) : ", Minor(mat1, 1, 1),
            "Cofactor(mat1, 0, 0) : ", Cofactor(mat1, 0, 0),
            "Cofactor(mat1, 0, 1) : ", Cofactor(mat1, 0, 1),
            "Cofactor(mat1, 0, 2) : ", Cofactor(mat1, 0, 2),
            "Det(mat1) : ", Det(mat1),
            "Transpose(mat1) : ", Transpose(mat1),
            "Adjoint(mat1) : ", Adjoint(mat1),
            "Invert(mat1) : ", Invert(mat1),
            "v1 : ", v1,
            "mat1 * mat1 : ", mat1 * mat1,
            "mat1 * v1 : ", mat1 * v1,
            "v1 * mat1 : ", v1 * mat1
    );
}

static void TestGeometry() {
    Ray3f ray;

    Vertex3f v1({-10, 0, 0});
    Vertex3f v2({10, 0, 0});
    Vertex3f v3({0, 10, 0});

    Triangle3f tri(v1, v2, v3);

    HitRecord record;

    Sphere sphere(10);
    Print(
            "ray : ", ray,
            "v1 : ", v1,
            "tri : ", tri,
            "record : ", record,
            "sphere : ", sphere
    );
}

static void TestMath() {
    Print(
            "ConvertDegreesToRadians(180) : ", ConvertDegreesToRadians(180),
            "ConvertRadiansToDegrees(1) : ", ConvertRadiansToDegrees(1),
            "Sin(60) : ", Sin(30),
            "Cos(60) : ", Cos(60),
            "Tan(60) : ", Tan(60)
    );
}

int main() {
    //TestVector();
    //TestMatrix();
    TestGeometry();
    //TestMath();
}
