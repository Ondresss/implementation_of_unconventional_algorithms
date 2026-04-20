//
// Created by andrew on 20.04.26.
//

#include "Menu.h"

void Menu::draw() {
    if (GuiButton({ 40, 350, 260, 40 }, "DRAW")) {
        float startX = GetScreenWidth() * 0.2;
        float startY = GetScreenHeight() * 0.5;
        this->terrain.draw(FractalTerrain::Line{Vector2{startX,startY},Vector2{startX + 200,startY}},10,5);
    }
}