#include "raylib.h"
#include <vector>

#include "Menu.h"
int main(void) {

    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Raylib - Fractal Landscape");

    SetTargetFPS(60);
    Menu menu{};
    Color myLightBlue = { 190, 230, 255, 255 };
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(myLightBlue);
        menu.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}