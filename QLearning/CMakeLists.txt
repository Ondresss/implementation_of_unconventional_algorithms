cmake_minimum_required(VERSION 3.20)
project(QLearning)

set(CMAKE_CXX_STANDARD 26)
find_package(raylib REQUIRED)
add_executable(QLearning main.cpp
        raygui.h
        Matrix.h
        IDrawable.h
        Menu.cpp
        Menu.h
        gui_impl.cpp
        Agent.cpp
        Agent.h
        QLearningVisualizer.cpp
        QLearningVisualizer.h
        IVisualizable.h
)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
target_compile_options(QLearning PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_options(QLearning PRIVATE -fsanitize=address -fsanitize=undefined)
target_link_libraries(QLearning PRIVATE raylib)