#include "Menu.h"

float Menu::calculateStep(int iters) {
    if (iters <= 1) return 40.0f;
    if (iters == 2) return 65.0f;
    if (iters == 3) return 85.0f;
    if (iters == 4) return 112.0f;
    return 5.0f;
}

void Menu::drawAndLogic() {
    if (this->isRunning){
        activeSystem->draw();
    }
    GuiGroupBox({ 20, 20, 300, 250 }, "L-SYSTEM CONFIG");

    GuiLabel({ 40, 50, 100, 20 }, "Rule (F -> ...):");
    if (GuiTextBox({ 40, 75, 260, 30 }, ruleBuffer, 128, editRule)) {
        editRule = !editRule;
    }

    GuiLabel({ 40, 120, 100, 20 }, "Iterations:");
    GuiValueBox({ 40, 145, 100, 30 }, nullptr, &iterValue, 0, 7, true);

    if (GuiButton({ 40, 200, 260, 40 }, "GENERATE & RUN")) {

        float step = calculateStep(iterValue);
        
        activeSystem = std::make_shared<LSystem>("F", LSystem::Rule{'F', ruleBuffer}, PI/7.0f, step);
        activeSystem->run(iterValue);
        this->isRunning = true;
    }
}