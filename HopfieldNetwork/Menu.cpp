#include "Menu.h"
void Menu::draw(const Rectangle& rec) {
    float spacing = 10.0f;
    float btnHeight = 40.0f;
    float previewSize = rec.width - (2 * spacing);

    Rectangle previewRect = {
        rec.x + spacing,
        static_cast<float>(rec.y - rec.y * 0.2),
        static_cast<float>(rec.width * 0.2),
        static_cast<float>(rec.width * 0.2)
    };

    this->pictures.at(this->currentPictureIndex).draw(previewRect);

    float currentY = rec.y + previewSize + (spacing * 2);
    Rectangle btnBounds = { rec.x + spacing, currentY, rec.width - (spacing), btnHeight };

    if (GuiButton(btnBounds, "RECOVER")) {
        network->recover(this->pictures.at(this->currentPictureIndex), 10);
    }

    currentY += btnHeight + spacing;
    btnBounds.y = currentY;
    if (GuiButton(btnBounds, "DESTROY")) {
        for(int i = 0; i < this->pictures.at(this->currentPictureIndex).numOfPixels(); ++i) {
            if (GetRandomValue(0, 10) > 7) {
                this->pictures.at(this->currentPictureIndex)(i) *= -1;
            }
        }
    }
    currentY += btnHeight + spacing;
    btnBounds.y = currentY;
    if (GuiButton(btnBounds, "NEXT")) {
        this->currentPictureIndex = (this->currentPictureIndex + 1) % this->pictures.size();
    }
    currentY += btnHeight + spacing;
    btnBounds.y = currentY;
    if (GuiButton(btnBounds, "CALCULATE ENERGY FUNCTION")) {
        this->energyTextValue = network->calculateEnergy(this->pictures.at(this->currentPictureIndex));
    }
    std::string energyStr = std::string("ENERGY FUNCTION: ") + std::to_string(this->energyTextValue).c_str();
    GuiLabel({ static_cast<float>(rec.width * 1.1), static_cast<float>(rec.height * 1.1), 180, 20 }, energyStr.c_str());
}