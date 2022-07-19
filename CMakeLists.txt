cmake_minimum_required(VERSION 3.22)
project(JustLab)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(
        include
)

add_executable(
        TestMath
        test/MathTester.cpp
)

add_executable(
        TestGraphics
        test/GraphicsTester.cpp
)

add_executable(
        ExampleRasterizer01
        example/rasterizer/african_head.cpp
)

add_executable(
        ExampleRayTracer01
        example/tracer/cornell_box.cpp
)