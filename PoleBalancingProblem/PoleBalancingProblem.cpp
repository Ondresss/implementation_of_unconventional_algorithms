#include "PoleBalancingProblem.h"
#include <iostream>
#include <iomanip>

void PoleBalancingProblem::run(int noIterations) {
    int curIter = 0;
    while (curIter < noIterations) {
        this->agent->nextStep(this->currentS);
        if (curIter % 1000 == 0) {
            std::cout << "Training Iteration: " << curIter << "/" << noIterations << "\r" << std::flush;
        }
        ++curIter;
    }
    std::cout << "\nQ-Learning training finished." << std::endl;
}

void PoleBalancingProblem::draw(const Rectangle& rec) {
    static int frameCounter = 0;
    this->currentScore++;
    arma::mat s_norm_mat(4, 1);
    s_norm_mat(0, 0) = currentS.Data()[0] / 2.4;
    s_norm_mat(1, 0) = currentS.Data()[1] / 3.0;
    s_norm_mat(2, 0) = currentS.Data()[2] / 0.21;
    s_norm_mat(3, 0) = currentS.Data()[3] / 4.0;

    arma::mat prediction;
    agent->getBrain().Predict(s_norm_mat, prediction);

    float confidence = static_cast<float>(prediction(0, 0));
    int actionIdx = (confidence > 0.5) ? 1 : 0;

    mlpack::CartPole::Action mlAction;
    mlAction.action = (actionIdx == 1) ?
                      mlpack::CartPole::Action::forward :
                      mlpack::CartPole::Action::backward;

    mlpack::CartPole::State nextS;
    agent->getEnv().Sample(currentS, mlAction, nextS);
    currentS = nextS;

    double x = currentS.Data()[0];
    double theta = currentS.Data()[2];

    frameCounter++;
    if (frameCounter >= 30) {
        std::cout << std::fixed << std::setprecision(3)
                  << "[Simulation] Pos: " << std::setw(6) << x
                  << " | Angle: " << std::setw(6) << theta
                  << " | Conf: " << confidence
                  << " | Action: " << (actionIdx == 1 ? "RIGHT" : "LEFT")
                  << std::endl;
        frameCounter = 0;
    }

    DrawText(TextFormat("Position (x): %.2f", x), rec.x + 20, rec.y + 50, 18, BLACK);
    DrawText(TextFormat("Angle (deg): %.2f", theta * (180.0/3.1415)), rec.x + 20, rec.y + 75, 18, (std::abs(theta) > 0.21 ? RED : DARKGRAY));
    DrawText(TextFormat("NN Confidence: %.4f", confidence), rec.x + 20, rec.y + 100, 18, BLUE);
    DrawText(TextFormat("Action: %s", (actionIdx == 1 ? "VPRAVO" : "VLEVO")), rec.x + 20, rec.y + 125, 18, DARKBLUE);
    DrawText(TextFormat("Current time: %i", currentScore), rec.x + 20, rec.y + 150, 18, DARKGREEN);
    DrawText(TextFormat("Best: %i", bestScore), rec.x + 20, rec.y + 175, 18, GOLD);
    if (std::abs(theta) > 0.21 || std::abs(x) > 2.4) {
        std::cout << "!!! PAD / RESET !!!" << std::endl;
        DrawText("!!! RESET !!!", rec.x + rec.width/2 - 50, rec.y + 150, 20, RED);
        if (currentScore >= bestScore) {
            this->bestScore = this->currentScore;
            this->currentScore = 0;
        }
        mlpack::CartPole::State startState;
        mlpack::CartPole::Action dummyAction;
        dummyAction.action = mlpack::CartPole::Action::backward;
        agent->getEnv().Sample(startState, dummyAction, currentS);
    }

    float scale = 80.0f;
    float centerX = rec.x + rec.width / 2.0f;
    float centerY = rec.y + rec.height / 2.0f + 50.0f;
    float cartX = centerX + (x * scale);
    float cartY = centerY;

    DrawLine(centerX - (2.4f * scale), cartY, centerX + (2.4f * scale), cartY, LIGHTGRAY);
    DrawRectangle(cartX - 30, cartY - 15, 60, 30, BLUE);

    float poleLength = 120.0f;
    float poleEndX = cartX + poleLength * std::sin(theta);
    float poleEndY = cartY - poleLength * std::cos(theta);

    DrawLineEx({cartX, cartY}, {poleEndX, poleEndY}, 5.0f, RED);
    DrawCircle(cartX, cartY, 5.0f, BLACK);
}