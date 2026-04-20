#include "raylib.h"
#include <vector>

#include "Menu.h"
int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Raylib - Fractal Landscape");

    SetTargetFPS(60);

    Menu menu{};
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Stiskni R pro novy teren", 10, 10, 20, GRAY);


        menu.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}