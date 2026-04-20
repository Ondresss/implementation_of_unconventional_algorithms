cmake_minimum_required(VERSION 3.20)
project(FractalLandscape)

set(CMAKE_CXX_STANDARD 26)
find_package(raylib REQUIRED)
add_executable(FractalLandscape main.cpp
        raygui.h
        gui_impl.cpp
        FractalTerrain.cpp
        FractalTerrain.h
        Menu.cpp
        Menu.h
)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
target_compile_options(FractalLandscape PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_options(FractalLandscape PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_libraries(FractalLandscape PRIVATE raylib)