#include <cstdlib>
#include <iostream>
#include <memory>
#include <raylib.h>

#include "LSystem.h"
#include "raygui.h"
#include "Menu.h"
int main(void) {
    const int screenWidth = 1000;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Q-Learning Vizualizace - 2D Bludiště");
    SetTargetFPS(60);

    Rectangle menuRect = { 10, 20, 250, (float)screenHeight - 40 };
    Rectangle visualizerRect = { 270, 20, (float)screenWidth - 280, (float)screenHeight - 40 };

    Color myBrown = { 245, 245, 220, 255 };

    std::string text = "F";
    LSystem::Rule rule = {'F',"F[+F]F[-F]F"};
    std::shared_ptr<LSystem> lsystem = std::make_shared<LSystem>(text,rule,PI / 8.0f,40);
    Menu menu(lsystem);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(myBrown);
        menu.drawAndLogic();

        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}