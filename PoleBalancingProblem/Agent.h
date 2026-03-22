//
// Created by andrew on 3/16/26.
//
#pragma once
#include "Matrix.h"
#include <cstdint>
#include <memory>
#include <random>
#include <utility>
#include "IDrawable.h"
#include <raylib.h>
#include <mlpack/core.hpp>
#include <mlpack/methods/reinforcement_learning/environment/cart_pole.hpp>
#include "Discretizer.h"
#include <mlpack/methods/ann/ffn.hpp>
#include <mlpack/methods/ann/layer/linear.hpp>
#include <mlpack/methods/ann/layer/layer.hpp>
#include <mlpack/methods/ann/loss_functions/mean_squared_error.hpp>
class Agent final : public IDrawable{
public:
    struct AgentParams {
        int bins = -1;
        int noStates = -1;
        int numActions = -1;
        std::vector<std::tuple<double, double>> limits{};
    };
    Agent(double gamma_,mlpack::CartPole& env_,AgentParams params_)
    :   gamma(gamma_),
        rng(std::random_device{}()),
        env(env_),
        params(std::move(params_)) {
        this->Q = std::make_shared<QLearning::Matrix<double>>(this->params.noStates,this->params.numActions,0);
        this->init();
    }
    void nextStep(mlpack::CartPole::State& currentS);
    void draw(const Rectangle& rec) override {}
    void init();
    mlpack::CartPole& getEnv() {return this->env;}
    mlpack::FFN<mlpack::MeanSquaredError>& getBrain() { return brain; }
    void trainFromSupervisor(int numSamples);

private:
    mlpack::FFN<mlpack::MeanSquaredError> brain;

    double gamma = -1;
    std::shared_ptr<QLearning::Matrix<double>> Q;
    std::mt19937 rng;
    mlpack::CartPole& env;
    AgentParams params{};
};
