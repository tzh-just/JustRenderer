
#include <Global.h>

#include <Math/Vector3.h>
#include <Math/Matrix4x4.h>
#include <Math/Transform.h>

#include <Tools/RNG.h>
#include <Tools//Timer.h>
#include <Tools/Loader.h>
#include <Math/Matrix4x4.h>
#include <Math/Color3.h>

#include "Core/Film.h"

static void TestVector();

static void TestMatrix();

using namespace Just;

static void ReadAndWriteImage() {
    Point2i resolution1(512, 512);
    Film film1(resolution1);
    film1.frameBuffer.resize(resolution1.x * resolution1.y);
    for (int i = 0; i < resolution1.x; i++) {
        for (int j = 0; j < resolution1.y; j++) {
            film1.frameBuffer[i * resolution1.x + j] = ToRGB(Spectrum(0.5f, 0, 0));
        }
    }
    film1.StoreImage("test/test1.tga", ImageType::TGA);


    auto texture = std::make_shared<Texture>();
    Loader::LoadTexture(texture, "scene/AfricanHead/Texture/Diffuse.tga");

    Point2i resolution2(texture->width, texture->height);
    Film film2(resolution2);
    film2.frameBuffer.resize(resolution2.x * resolution2.y);
    for (int i = 0; i < resolution2.x; i++) {
        for (int j = 0; j < resolution2.y; j++) {
            film2.frameBuffer[i * resolution2.x + j] = texture->pixels[i * resolution2.x + j];
        }
    }
    film2.StoreImage("test/test2.tga", ImageType::TGA);
}

int main() {
    //TestVector();
    //TestMatrix();
    ReadAndWriteImage();
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