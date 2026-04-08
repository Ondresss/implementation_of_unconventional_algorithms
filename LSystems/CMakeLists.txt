cmake_minimum_required(VERSION 3.20)
project(LSystems)

set(CMAKE_CXX_STANDARD 26)
find_package(raylib REQUIRED)
add_executable(LSystems main.cpp
        raygui.h
        IDrawable.h
        gui_impl.cpp
        LSystem.cpp
        LSystem.h
        Turtle.cpp
        Turtle.h
        Menu.cpp
        Menu.h
        ../IFS/main.cpp
        ../IFS/IFS.cpp
        ../IFS/IFS.h
)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
target_compile_options(LSystems PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_options(LSystems PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_libraries(LSystems PRIVATE raylib)