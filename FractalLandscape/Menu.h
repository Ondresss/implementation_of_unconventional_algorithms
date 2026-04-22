//
// Created by andrew on 20.04.26.
//
#pragma once
#include "FractalTerrain.h"
#include "raygui.h"
class Menu {
public:
    Menu() = default;
    void draw();
private:
    FractalTerrain terrain{};
    bool showTerrain = false;
    int currentSeed = 0;
    int depths[4] = { 5, 10, 10, 8 };
    bool editDepth[4] = { false, false, false, false };
    char ruleBuffer[1024] = {0};
};
