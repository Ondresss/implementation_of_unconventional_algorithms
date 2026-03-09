cmake_minimum_required(VERSION 3.20)
project(HopfieldNetwork)

set(CMAKE_CXX_STANDARD 26)
find_package(raylib REQUIRED)
add_executable(HopfieldNetwork main.cpp
        raygui.h
        HopfieldNetwork.cpp
        HopfieldNetwork.h
        Picture.cpp
        Picture.h
        Matrix.h
        IFunction.h
        Signum.cpp
        Signum.h
        IDrawable.h
        Menu.cpp
        Menu.h
        gui_impl.cpp
)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
target_compile_options(HopfieldNetwork PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_options(HopfieldNetwork PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_libraries(HopfieldNetwork PRIVATE raylib
)