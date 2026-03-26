#include <iostream>
#include <mlpack/core.hpp>
#include <mlpack/methods/reinforcement_learning/environment/cart_pole.hpp>
#include <raylib.h>
#include "Agent.h"
#include "PoleBalancingProblem.h"
#include <cmath>
int main() {
    mlpack::CartPole env;

    Agent::AgentParams params;
    params.bins = 10;
    params.numActions = 2;

    params.noStates = std::pow(params.bins, 4);

    params.limits = {
                {-2.4, 2.4},
                {-3.0, 3.0},
                {-0.21, 0.21},
                {-4.0, 4.0}
    };

    auto agent = std::make_shared<Agent>(0.99, env, params);

    auto problem = std::make_unique<PoleBalancingProblem>(agent);
    std::cout << "QLearning........." << std::endl;
    problem->run(1000000);
    std::cout << "QLearning ended" << std::endl;
    std::cout << "Faze 2: Supervisor training..." << std::endl;
    agent->trainFromSupervisor(80000);
    std::cout << "Faze 2: Supervisor training ended" << std::endl;
    InitWindow(800, 450, "CartPole Q-Learning");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        problem->draw({ 0, 0, 800, 450 });
        DrawText("Student (Neural Network) in control", 20, 20, 20, DARKGREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}