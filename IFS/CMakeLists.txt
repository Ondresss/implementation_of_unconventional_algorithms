cmake_minimum_required(VERSION 3.20)
project(IFS)

set(CMAKE_CXX_STANDARD 26)

find_package(Matplot++ REQUIRED)
add_executable(IFS main.cpp
        IFS.cpp
        IFS.h
        IVisualizable.h
        Matrix.h)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
target_compile_options(IFS PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_options(IFS PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_libraries(IFS PRIVATE
        Matplot++::matplot
)