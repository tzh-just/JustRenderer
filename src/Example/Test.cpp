
#include "Just/Math/Vector.h"
#include "Just/Math/Matrix.h"
#include "Just/Geometry/Transform.h"
#include "Just/Geometry/Ray.h"
#include "Just/Geometry/Vertex.h"
#include "Just/Geometry/Triangle.h"

using namespace Just;

static void TestVector() {
    Vector3f v0;//缺省构造
    std::cout << "v0 = " << v0 << std::endl;
    Vector3f v1(1);//参数构造
    std::cout << "v1 = " << v1 << std::endl;
    Vector3f v2{2, 2, 2};//拷贝构造
    std::cout << "v2 = " << v2 << std::endl;
    Vector3f v3;//拷贝赋值
    v3 = v2 + v1;
    std::cout << "v3 = " << v3 << std::endl;
    Vector3f v4{1, 1, -1};//初始化列表
    std::cout << "v4 = " << v4 << std::endl;
    std::cout << "===========================================================" << std::endl;

    //四则运算
    std::cout << "v0 + v1 = " << v0 + v1 << std::endl;
    std::cout << "v2 - v1= " << v2 - v1 << std::endl;
    std::cout << "v2 * v3= " << v2 * v3 << std::endl;

    //数乘
    std::cout << "2 * v1 = " << 2.0f * v1 << std::endl;
    std::cout << "v1 * 2 = " << v1 * 2.0f << std::endl;
    std::cout << "v1 / 2 = " << v1 / 2.0f << std::endl;
    std::cout << "===========================================================" << std::endl;

    //赋值四则
    v1 += v2;
    std::cout << "v1 += v2 = " << v1 << std::endl;
    v1 -= v2;
    std::cout << "v1 -= v2 = " << v1 << std::endl;
    v1 *= v2;
    std::cout << "v1 *= v2 = " << v1 << std::endl;
    //赋值数乘
    v1 *= 2.0f;
    std::cout << "v1 *= 2 = " << v1 << std::endl;
    v1 /= 2.0f;
    std::cout << "v1 /= 2 = " << v1 << std::endl;
    std::cout << "===========================================================" << std::endl;

    //长度/模
    std::cout << "Length(v1) = " << Length(v1) << std::endl;
    std::cout << "Norm(v1) = " << Norm(v1) << std::endl;
    //点积
    std::cout << "Dot(v1, v2) = " << Dot(v1, v2) << std::endl;
    //叉积
    std::cout << "Cross(v1, v4) = " << Cross(v1, v4) << std::endl;
    //归一化
    std::cout << "Normalize(v1) = " << Normalize(v1) << std::endl;
    std::cout << "Length(Normalize(v1)) = " << Length(Normalize(v1)) << std::endl;
}

static void TestMatrix() {
    Matrix3f mat0;
    Matrix3f mat1 = mat0;
    mat1.SetRow(0, {1, 1, 1});
    mat1.SetCol(2, {1, 1, 1});
    std::cout << "mat0 = \n" << mat0 << std::endl;
    std::cout << "mat1 = \n" << mat1 << std::endl;
    std::cout << "mat1.Row(0) = " << mat1.Row(0) << std::endl;
    std::cout << "mat1.Col(0) = " << mat1.Col(0) << std::endl;
    std::cout << "===========================================================" << std::endl;

    //加减
    std::cout << "mat1 + mat0 = \n" << mat1 + mat0 << std::endl;
    std::cout << "mat0 - mat1 = \n" << mat0 - mat1 << std::endl;
    //数乘
    std::cout << "2 * mat1 = \n" << 2.0f * mat1 << std::endl;
    std::cout << "mat1 * 2 = \n" << mat1 * 2.0f << std::endl;
    std::cout << "mat1 / 2 = \n" << mat1 / 2.0f << std::endl;
    std::cout << "===========================================================" << std::endl;

    Matrix4f mat2 = {
            {2,  -1, 1, 3},
            {1,  4,  0, 0},
            {-2, 0,  2, 0},
            {5,  0,  0, -3}
    };
    std::cout << "mat2 = \n" << mat2 << std::endl;
    //余子式
    std::cout << "Minor(mat2, 1, 1) = \n" << Minor(mat2, 1, 1) << std::endl;
    //代数余子式
    std::cout << "Cofactor(mat2, 0, 0) = " << Cofactor(mat2, 0, 0) << std::endl;
    std::cout << "Cofactor(mat2, 0, 1) = " << Cofactor(mat2, 0, 1) << std::endl;
    std::cout << "Cofactor(mat2, 0, 2) = " << Cofactor(mat2, 0, 2) << std::endl;
    std::cout << "Cofactor(mat2, 0, 3) = " << Cofactor(mat2, 0, 3) << std::endl;
    std::cout << "Det(mat2) = " << Det(mat2) << std::endl;
    std::cout << "===========================================================" << std::endl;

    Matrix3f mat3 = {
            {1, 2, 3},
            {2, 2, 1},
            {3, 4, 3}
    };
    std::cout << "mat3 = \n" << mat3 << std::endl;
    //转置矩阵
    std::cout << "Transpose(mat3) = \n" << Transpose(mat3) << std::endl;
    //伴随矩阵
    std::cout << "Adjoint(mat3) = \n" << Adjoint(mat3) << std::endl;
    //逆矩阵
    std::cout << "Invert(mat3) = \n" << Invert(mat3) << std::endl;
    std::cout << "===========================================================" << std::endl;

    Matrix<2, 3, float> mat5 = {
            {1, 2, 5},
            {2, 4, 6}
    };
    Matrix<3, 2, float> mat6 = {
            {1, 2},
            {3, 2},
            {4, 1}
    };
    Vector3f v0(1, 2, 3);
    std::cout << "v0 = " << v0 << std::endl;
    std::cout << "mat5 = \n" << mat5 << std::endl;
    std::cout << "mat6 = \n" << mat6 << std::endl;
    //矩阵左乘
    std::cout << "mat5 * mat6 = \n" << mat5 * mat6 << std::endl;
    //列向量左乘
    std::cout << "mat5 * v0 = " << mat5 * v0 << std::endl;
    //行向量右乘
    std::cout << "v0 * mat6 = " << v0 * mat6 << std::endl;
}

static void TestAny() {
    Ray3f ray;
    std::cout << "ray = " << std::endl << ray << std::endl;
    Vertex3f a({-10, 0, 0});
    Vertex3f b({10, 0, 0});
    Vertex3f c({0, 10, 0});
    std::cout << "a = " << std::endl << a << std::endl;
    Triangle3f t(a, b, c);
    std::cout << "t = " << std::endl << t << std::endl;
}

int main() {
    //TestVector();
    //TestMatrix();
    TestAny();
}
