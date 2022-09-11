cmake_minimum_required(VERSION 3.22)
project(JustRenderer)

set(CMAKE_CXX_STANDARD 20)

# 设置相对路径
set(CMAKE_HOME_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}")

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")


# 配置OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(
        ext
        include
)

add_executable(
        test
        src/test/Test.cpp
)

add_executable(
        cbox
        src/cbox/CornellBox.cpp
)