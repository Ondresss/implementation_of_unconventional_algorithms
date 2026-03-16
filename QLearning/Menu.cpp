#include "Menu.h"

#include <iostream>
#include <ostream>

void Menu::draw(const Rectangle& menuRec, const Rectangle& visualizerRec) {
    float spacing = 15.0f;
    float btnHeight = 40.0f;

    if (this->visualizePath) {
        this->visualizer->visualizePath(visualizerRec);
    }
    else if (this->visualizeStart) {
        this->visualizer->visualize(visualizerRec);
    }
    else if (this->visualizerInitialized) {
        this->visualizer->visualizeStart(visualizerRec);
    }
    if (this->visualizer->visualizePathStop()) {
        this->visualizePath = false;
    }
    if (this->visualizer->shouldStop()) {
        this->visualizeStart = false;
    }

    float currentY = menuRec.y + spacing;

    Rectangle btnBounds = {
        menuRec.x + spacing,
        currentY,
        menuRec.width - (2 * spacing),
        btnHeight
    };

    if (GuiButton(btnBounds, "RANDOM START")) {
        this->visualizerInitialized = true;
        this->visualizer->setup();
    }

    currentY += btnHeight + spacing;
    btnBounds.y = currentY;

    if (GuiButton(btnBounds, "LEARN")) {
        this->visualizeStart = true;
    }
    currentY += btnHeight + spacing;
    btnBounds.y = currentY;
    if (GuiButton(btnBounds, "FIND")) {
        this->visualizePath = true;
    }


    DrawRectangleLinesEx(menuRec, 1, DARKGRAY);
}
