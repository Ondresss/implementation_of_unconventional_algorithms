cmake_minimum_required(VERSION 3.20)
project(PoleBalancingProblem)

set(CMAKE_CXX_STANDARD 26)

find_package(Armadillo REQUIRED)
find_package(raylib REQUIRED)

add_executable(PoleBalancingProblem main.cpp
        Discretizer.h
        Agent.cpp
        Agent.h
        PoleBalancingProblem.cpp
        PoleBalancingProblem.h
        ../FractalLandscape/main.cpp)

target_include_directories(PoleBalancingProblem PRIVATE
        /usr/local/include
)

target_link_libraries(PoleBalancingProblem PRIVATE
        armadillo
        raylib
)

target_compile_options(PoleBalancingProblem PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_options(PoleBalancingProblem PRIVATE -fsanitize=address -fsanitize=undefined)