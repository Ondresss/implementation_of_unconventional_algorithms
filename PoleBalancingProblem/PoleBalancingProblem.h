#pragma once
#include "Agent.h"
#include <mlpack/methods/reinforcement_learning/environment/cart_pole.hpp>

class PoleBalancingProblem : public IDrawable {
public:
    PoleBalancingProblem(std::shared_ptr<Agent> agent_)
        : agent(std::move(agent_))  {
        this->currentS.Data() = arma::vec({0.0, 0.0, 0.05, 0.0});
        this->env = this->agent->getEnv();
    };

    void run(int noIterations);
    void draw(const Rectangle& rec) override;

private:
    std::shared_ptr<Agent> agent = nullptr;
    mlpack::CartPole::State currentS;
    mlpack::CartPole env;
    int currentScore = 0;
    int bestScore = 0;
};