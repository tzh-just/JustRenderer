
#include <just/array.h>

using namespace Just;

static void TestPoint() {
    std::cout << "==========================" << std::endl;
    std::cout << "TEST: POINT" << std::endl;
    std::cout << "==========================" << std::endl;

    Point3f p0;//缺省构造
    std::cout << "p0 = " << p0 << std::endl;

    Point3f p1(1);//参数构造
    std::cout << "p1 = " << p1 << std::endl;

    Point3f p2{2, 2, 2};//拷贝构造
    std::cout << "p2 = " << p2 << std::endl;

    Point3f p3;//拷贝赋值
    p3 = p2 + p1;
    std::cout << "p3 = " << p3 << std::endl;
    std::cout << "--------------------------" << std::endl;

    //运算符重载
    std::cout << "p1 + p0 = " << p1 + p0 << std::endl;
    std::cout << "p1 - p0 = " << p1 - p0 << std::endl;
}

static void TestVector() {
    std::cout << "==========================" << std::endl;
    std::cout << "TEST: VECTOR" << std::endl;
    std::cout << "==========================" << std::endl;

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
    std::cout << "--------------------------" << std::endl;

    //四则运算
    std::cout << "v0 + v1 = " << v0 + v1 << std::endl;
    std::cout << "v2 - v1= " << v2 - v1 << std::endl;
    std::cout << "v2 * v3= " << v2 * v3 << std::endl;
    std::cout << "--------------------------" << std::endl;

    //数乘
    std::cout << "2 * v1 = " << 2.0f * v1 << std::endl;
    std::cout << "v1 * 2 = " << v1 * 2.0f << std::endl;
    std::cout << "v1 / 2 = " << v1 / 2.0f << std::endl;
    std::cout << "--------------------------" << std::endl;

    //长度/模
    std::cout << "Length(v1) = " << Length(v1) << std::endl;
    std::cout << "Norm(v1) = " << Norm(v1) << std::endl;
    std::cout << "--------------------------" << std::endl;

    //点积
    std::cout << "Dot(v1, v2) = " << Dot(v1, v2) << std::endl;
    std::cout << "--------------------------" << std::endl;

    //叉积
    std::cout << "Cross(v1, v4) = " << Cross(v1, v4) << std::endl;
    std::cout << "--------------------------" << std::endl;

    //归一化
    std::cout << "Normalize(v1) = " << Normalize(v1) << std::endl;
    std::cout << "Length(Normalize(v1)) = " << Length(Normalize(v1)) << std::endl;
}

static void TestMatrix() {
    std::cout << "==========================" << std::endl;
    std::cout << "TEST: MATRIX" << std::endl;
    std::cout << "==========================" << std::endl;
    Matrix3f mat0;
    std::cout << "mat0 = \n" << mat0 << std::endl;
    std::cout << "--------------------------" << std::endl;

    Matrix3f mat1 = mat0;
    mat1.SetRow(0, {1, 1, 1});
    mat1.SetCol(2, {1, 1, 1});
    std::cout << "mat1 = \n" << mat1 << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "mat1.Row(0) = \n" << mat1.Row(0) << std::endl;
    std::cout << "mat1.Col(0) = \n" << mat1.Col(0) << std::endl;
    std::cout << "--------------------------" << std::endl;

    Matrix3f mat2 = Matrix3f::Identity() * 4.0f + Matrix3f::Zero();
    std::cout << "mat2 = \n" << mat2 << std::endl;
    std::cout << "--------------------------" << std::endl;
    //运算符
    std::cout << "mat2 + mat1 = \n" << mat1 + mat2 << std::endl;
    std::cout << "mat2 - mat1 = \n" << mat2 - mat1 << std::endl;
    std::cout << "--------------------------" << std::endl;

    //余子式/代数余子式
    Matrix4f mat3 = {
            {2,  -1, 1, 3},
            {1,  4,  0, 0},
            {-2, 0,  2, 0},
            {5,  0,  0, -3}
    };
    std::cout << "mat3 = \n" << mat3 << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Minor(mat3, 1, 1) = \n" << Minor(mat3, 1, 1) << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Cofactor(mat3, 0, 0) = " << Cofactor(mat3, 0, 0) << std::endl;
    std::cout << "Cofactor(mat3, 0, 1) = " << Cofactor(mat3, 0, 1) << std::endl;
    std::cout << "Cofactor(mat3, 0, 2) = " << Cofactor(mat3, 0, 2) << std::endl;
    std::cout << "Cofactor(mat3, 0, 3) = " << Cofactor(mat3, 0, 3) << std::endl;
    std::cout << "--------------------------" << std::endl;
    //行列式
    std::cout << "Det(mat3) = " << Det(mat3) << std::endl;
    std::cout << "--------------------------" << std::endl;

    Matrix3f mat4 = {
            {1, 2, 3},
            {2, 2, 1},
            {3, 4, 3}
    };
    std::cout << "mat4 = \n" << mat4 << std::endl;
    std::cout << "--------------------------" << std::endl;
    //转置矩阵
    std::cout << "Transpose(mat4) = \n" << Transpose(mat4) << std::endl;
    std::cout << "--------------------------" << std::endl;
    //伴随矩阵
    std::cout << "Adjoint(mat4) = \n" << Adjoint(mat4) << std::endl;
    std::cout << "--------------------------" << std::endl;
    //逆矩阵
    std::cout << "Invert(mat4) = \n" << Invert(mat4) << std::endl;

    //矩阵乘法
    Matrix<2, 3, float> mat5 = {
            {1, 2, 5},
            {2, 4, 6}
    };
    std::cout << "mat5 = \n" << mat5 << std::endl;
    std::cout << "--------------------------" << std::endl;
    Matrix<3, 2, float> mat6 = {
            {1, 2},
            {3, 2},
            {4, 1}
    };
    std::cout << "mat6 = \n" << mat6 << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "mat5 * mat6 = \n" << mat5 * mat6 << std::endl;
}

int main() {
    TestPoint();
    TestVector();
    TestMatrix();
}
