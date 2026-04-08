#include "Menu.h"

float Menu::calculateStep(int iters) {
    if (iters <= 1) return 40.0f;
    if (iters == 2) return 65.0f;
    if (iters == 3) return 85.0f;
    if (iters == 4) return 112.0f;
    return 200.0f;
}
void Menu::drawAndLogic() {
    if (this->isRunning && activeSystem) {
        activeSystem->draw();
    }

    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(DARKGRAY));
    GuiGroupBox({ 20, 20, 300, 420 }, "L-SYSTEM CONFIG");
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(RAYWHITE));
    GuiLabel({ 40, 50, 100, 20 }, "Axiom:");
    if (GuiTextBox({ 40, 70, 260, 30 }, this->axiomBuffer, 128, this->editAxiom)) {
        this->editAxiom = !this->editAxiom;
    }

    GuiLabel({ 40, 110, 100, 20 }, "Rule (F -> ...):");
    if (GuiTextBox({ 40, 130, 260, 30 }, ruleBuffer, 128, editRule)) {
        editRule = !editRule;
    }

    GuiLabel({ 40, 180, 100, 20 }, "Iterations:");
    GuiValueBox({ 40, 200, 100, 30 }, nullptr, &iterValue, 0, 8, true);

    GuiLabel({ 40, 240, 260, 20 }, "Rotation Angle (rad):");

    if (GuiValueBoxFloat({ 40, 265, 120, 30 }, "", angleBuffer, &this->angle, editAngle)) {
        this->editAngle = !this->editAngle;
    }
    if (GuiButton({ 40, 350, 260, 40 }, "GENERATE & RUN")) {
        float step = calculateStep(iterValue);

        activeSystem = std::make_shared<LSystem>(this->axiomBuffer, LSystem::Rule{'F', ruleBuffer}, PI/7.0f, step);
        activeSystem->run(iterValue);
        this->isRunning = true;
    }
}