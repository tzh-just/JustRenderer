cmake_minimum_required(VERSION 3.22)
project(just)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(
        Dependencies
        JustLab
)

add_executable(
        TestMath
        Test/MathTester.cpp
        JustLab/Geometry/Vector2.h JustLab/Geometry/Point2.h JustLab/Geometry/Matrix2.h JustLab/Geometry/Matrix3.h JustLab/Geometry/Point4.h JustLab/Geometry/Vector4.h)
