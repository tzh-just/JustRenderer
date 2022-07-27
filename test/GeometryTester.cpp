
#include "Global.h"
#include "Geometry/Ray.h"
#include "Geometry/Triangle.h"
#include "Geometry/Sphere.h"

using namespace Just;

static void TestGeometry() {
    Ray3f ray;

    HitRecord record;

    Sphere sphere(10);

    Print(
            "ray : ", ray,
            "record : ", record,
            "sphere : ", sphere
    );
}

int main() {
    TestGeometry();
}
