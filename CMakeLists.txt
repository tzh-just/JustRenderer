cmake_minimum_required(VERSION 3.22)
project(JustLab)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(
        Dependencies
        JustLab
)

add_executable(
        TestMath
        Test/MathTester.cpp
)

add_executable(
        TestGeometry
        Test/GeometryTester.cpp
)