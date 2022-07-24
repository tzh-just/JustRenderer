
#include "Global.h"
#include "Math/VectorExt.h"
#include "Math/MatrixExt.h"
#include "Math/Transform.h"
#include "Math/Quaternion.h"

using namespace Just;

static void TestVector() {
    Vector3f v1(2, 0, 0), v2(0, 2, 0);
    Print(
            "v1", v1,
            "v2", v2,
            "Length(v1) = ", Length(v1),
            "Dot(v1, v2)", Dot(v1, v2),
            "Cross(v1, v2) = ", Cross(v1, v2),
            "Normalize(v1) = ", Normalize(v1),
            "Length(Normalize(v1)) = ", Length(Normalize(v1))
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
            "Minor(mat1, 1, 1) = ", Minor(mat1, 1, 1),
            "Cofactor(mat1, 0, 0) = ", Cofactor(mat1, 0, 0),
            "Cofactor(mat1, 0, 1) = ", Cofactor(mat1, 0, 1),
            "Cofactor(mat1, 0, 2) = ", Cofactor(mat1, 0, 2),
            "Det(mat1) = ", Det(mat1),
            "Transpose(mat1) = ", Transpose(mat1),
            "Adjoint(mat1) = ", Adjoint(mat1),
            "Invert(mat1) = ", Invert(mat1),
            "v1 = ", v1,
            "mat1 * mat1 = ", mat1 * mat1,
            "mat1 * v1 = ", mat1 * v1,
            "v1 * mat1 = ", v1 * mat1
    );
}

static void TestMath() {
    Print(
            "Radians(180) = ", Radians(180),
            "Degrees(1) = ", Degrees(1),
            "Sin(60) = ", Sin(30),
            "Cos(60) = ", Cos(60),
            "Tan(60) = ", Tan(60)
    );
}

static void TestTransform() {

}

static void TestQuaternion() {

}

int main() {
    //TestVector();
    TestMatrix();
    //TestMath();
    //TestQuaternion();
}
