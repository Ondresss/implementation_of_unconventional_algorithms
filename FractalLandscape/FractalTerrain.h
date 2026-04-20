//
// Created by andrew on 20.04.26.
//
#pragma once
#include <tuple>
#include <raylib.h>
class FractalTerrain {
public:
    struct Line
    {
        Vector2 start{};
        Vector2 end{};
    };
    FractalTerrain() = default;
    void draw(const Line& line,int depth,int amplitude);
};

