//
// Created by andrew on 20.04.26.
//

#include "Menu.h"

void Menu::draw() {
    if (GuiButton({ 40, (float)GetScreenHeight() - 60, 200, 40 }, "GENERATE TERRAIN")) {
        this->showTerrain = true;
        this->currentSeed = GetRandomValue(0,23456);
    }
    if (showTerrain) {
        SetRandomSeed(this->currentSeed);
        float floorY = GetScreenHeight() * 0.7f;
        this->terrain.draw(FractalTerrain::Line{
          {0, floorY-150}, {static_cast<float>(GetScreenWidth()), floorY-150}},
          5, 250.0f,WHITE);
        this->terrain.draw(FractalTerrain::Line{
            {0, floorY-100}, {static_cast<float>(GetScreenWidth()), floorY-100}},
            10, 120.0f,BROWN);
        this->terrain.draw(FractalTerrain::Line{
            {0, floorY-60}, {static_cast<float>(GetScreenWidth()), floorY-60}},
            10, 80.0f,DARKGREEN);
        this->terrain.draw(FractalTerrain::Line{
           {0, floorY+150}, {static_cast<float>(GetScreenWidth()), floorY+150}},
           8, 10.0f,GREEN);




    }
}