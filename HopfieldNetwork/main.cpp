//
// Created by andrew on 08.03.26.
//
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ostream>

#include "HopfieldNetwork.h"
#include "Picture.h"
#include "Signum.h"
#include "IFunction.h"
#include "Menu.h"
int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Hopfieldova sit - Vizualizace");

    SetTargetFPS(60);
    GuiLoadStyle("../style_sunny.rgs");
    std::vector<std::vector<int8_t>> patternL = {
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1}
    };
    Picture picL(patternL);
    std::vector<Picture> pictures;
    pictures.push_back(picL);
    std::shared_ptr<IFunction> signum = std::make_shared<Signum>("Signum");
    std::shared_ptr<HopfieldNetwork> network = std::make_shared<HopfieldNetwork>(pictures,signum);
    network->train();
    Rectangle drawingArea = { 250, 100, 340, 640 };
    Menu menu(pictures,network);
    Color myBrown = { 245, 245, 220, 255 };
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(myBrown);

        menu.draw(drawingArea);


        EndDrawing();
    }

    CloseWindow();


    std::exit(EXIT_SUCCESS);
}
