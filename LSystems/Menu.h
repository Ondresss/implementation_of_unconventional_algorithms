#pragma once
#include <raylib.h>
#include "raygui.h"
#include <string>
#include "LSystem.h"

class Menu {
public:
    explicit Menu(std::shared_ptr<LSystem> activeSystem_)
    : activeSystem(std::move(activeSystem_)) {}

    void drawAndLogic();

private:
    char ruleBuffer[128] = "F[+F]F[-F]F";
    char axiomBuffer[128]  = "F";
    char angleBuffer[32] = "0.448";
    int iterValue = 4;
    bool editRule = false;
    bool editAxiom = false;
    bool isRunning = false;
    bool editAngle = false;
    float angle = PI / 6;
    std::shared_ptr<LSystem> activeSystem = nullptr;

    float calculateStep(int iters);
};