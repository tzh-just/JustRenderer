
#include <just/math.h>

using namespace Just;

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

    //四则运算
    std::cout << "v0 + v1 = " << v0 + v1 << std::endl;
    std::cout << "v2 - v1= " << v2 - v1 << std::endl;
    std::cout << "v2 * v3= " << v2 * v3 << std::endl;

    //数乘
    std::cout << "2 * v1 = " << 2.0f * v1 << std::endl;
    std::cout << "v1 * 2 = " << v1 * 2.0f << std::endl;
    std::cout << "v1 / 2 = " << v1 / 2.0f << std::endl;

    //长度/模
    std::cout << "length of v1 = " << Length(v1) << std::endl;
    std::cout << "norm of v1 = " << Norm(v1) << std::endl;
    //点积
    std::cout << "v1 dot v2 = " << Dot(v1, v2) << std::endl;
    //叉积
    std::cout << "v1 cross v4 = " << Cross(v1, v4) << std::endl;
    //归一化
    std::cout << "normalized v1 = " << Normalize(v1) << std::endl;
    std::cout << "length of normalized v1 = " << Length(Normalize(v1)) << std::endl;
}

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

    //运算符重载
    std::cout << "p1 + p0 = " << p1 + p0 << std::endl;
    std::cout << "p1 - p0 = " << p1 - p0 << std::endl;
}

static void TestMatrix() {
    std::cout << "==========================" << std::endl;
    std::cout << "TEST: MATRIX" << std::endl;
    std::cout << "==========================" << std::endl;
    Matrix3f m0;
    std::cout << "m0 = \n" << m0 << std::endl;

    Matrix3f m1;
    m1.SetRow(0, {1, 0, 0});
    m1.SetRow(1, {0, 1, 0});
    m1.SetRow(2, {0, 0, 1});
    std::cout << "m1 = \n" << m1 << std::endl;

    Matrix3f m2 = Matrix3f::Identity() * 4.0f;
    std::cout << "m2 = \n" << m2 << std::endl;

    Matrix3f m3 = Matrix3f::Zero() + m2 / 2.0f;
    std::cout << "m3 = \n" << m3 << std::endl;

    //运算符
    std::cout << "m2 + m1 = \n" << m1 + m2 << std::endl;
    std::cout << "m2 - m1 = \n" << m2 - m1 << std::endl;
    std::cout << "m3 - m2 = \n" << m2 * m3 << std::endl;
}

int main() {
    TestPoint();
    TestVector();
    TestMatrix();
}
