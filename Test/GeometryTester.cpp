
#include "Global.h"
#include "Geometry/Vertex.h"
#include "Geometry/Ray.h"
#include "Geometry/Triangle.h"
#include "Geometry/Sphere.h"

using namespace Just;

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

int main() {
    TestGeometry();
}
