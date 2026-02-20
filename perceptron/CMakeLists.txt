cmake_minimum_required(VERSION 4.0)
project(perceptron)

set(CMAKE_CXX_STANDARD 26)

find_package(Matplot++ REQUIRED)
add_executable(perceptron main.cpp
        Perceptron.cpp
        Perceptron.h
        Point.h
        PointLoader.cpp
        PointLoader.h
        IVisualizable.h
        IFunction.h
        Signum.cpp
        Signum.h
        PointSet.h)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

target_link_libraries(perceptron PRIVATE
        Matplot++::matplot
)