//
// Created by andrew on 20.04.26.
//
#pragma once
#include "FractalTerrain.h"
class Menu {
public:
    Menu() = default;
    void draw();
private:
    FractalTerrain terrain{};
};
