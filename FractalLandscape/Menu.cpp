//
// Created by andrew on 20.04.26.
//

#include "Menu.h"
void Menu::draw() {
    float panelX = static_cast<float>(GetScreenWidth() - 280);
    float startY = 20.0f;

    if (GuiButton({ panelX, startY, 260, 40 }, "GENERATE TERRAIN")) {
        this->showTerrain = true;
        this->currentSeed = GetRandomValue(0, 23456);
    }

    float vBoxY = startY + 60.0f;
    const char* labels[4] = { "Velehory Depth:", "Hnede hory Depth:", "Zelene hory Depth:", "Louka Depth:" };

    if (showTerrain) {
        SetRandomSeed(this->currentSeed);
        float floorY = GetScreenHeight() * 0.7f;

        this->terrain.draw(FractalTerrain::Line{
          {0, floorY - 150}, {static_cast<float>(GetScreenWidth()), floorY - 150}},
          depths[0], 250.0f, WHITE);

        this->terrain.draw(FractalTerrain::Line{
            {0, floorY - 100}, {static_cast<float>(GetScreenWidth()), floorY - 100}},
            depths[1], 120.0f, BROWN);

        this->terrain.draw(FractalTerrain::Line{
            {0, floorY - 60}, {static_cast<float>(GetScreenWidth()), floorY - 60}},
            depths[2], 80.0f, DARKGREEN);

        this->terrain.draw(FractalTerrain::Line{
           {0, floorY + 150}, {static_cast<float>(GetScreenWidth()), floorY + 150}},
           depths[3], 10.0f, GREEN);
    }
    for (int i = 0; i < 4; i++) {
        GuiLabel({ panelX, vBoxY, 200, 20 }, labels[i]);
        if (GuiValueBox({ panelX, vBoxY + 20, 260, 30 }, nullptr, &depths[i], 0, 15, editDepth[i])) {
            editDepth[i] = !editDepth[i];
        }
        vBoxY += 60.0f;
    }

}