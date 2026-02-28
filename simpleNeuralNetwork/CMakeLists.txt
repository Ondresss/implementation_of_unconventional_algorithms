cmake_minimum_required(VERSION 3.20)
project(perceptron)

set(CMAKE_CXX_STANDARD 26)

find_package(Matplot++ REQUIRED)
add_executable(perceptron main.cpp
        Perceptron.cpp
        Perceptron.h
        Point.h
        IFunction.h
        Signum.cpp
        Signum.h
        NeuralNetwork.cpp
        NeuralNetwork.h
        Sigmoid.cpp
        Sigmoid.h
)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
target_compile_options(perceptron PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_options(perceptron PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_libraries(perceptron PRIVATE
        Matplot++::matplot
)