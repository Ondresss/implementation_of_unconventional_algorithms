#include "Agent.h"
#include <iostream>

void Agent::nextStep(mlpack::CartPole::State& currentS) {
    if (std::abs(currentS.Data()[2]) > 0.21 || std::abs(currentS.Data()[0]) > 2.4) {
        mlpack::CartPole::Action resAct;
        resAct.action = mlpack::CartPole::Action::backward;
        env.Sample(currentS, resAct, currentS);
        return;
    }

    int fromState = Discretizer::getDiscreteState(params.limits, currentS.Data(), params.bins);

    double epsilon = 0.4;
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    int actionIdx;

    if (dist(rng) < epsilon) {
        actionIdx = std::uniform_int_distribution<int>(0, 1)(this->rng);
    } else {
        actionIdx = (Q->at(fromState, 0) >= Q->at(fromState, 1)) ? 0 : 1;
    }

    mlpack::CartPole::Action mlAction;
    mlAction.action = (actionIdx == 0) ? mlpack::CartPole::Action::backward : mlpack::CartPole::Action::forward;

    mlpack::CartPole::State nextS;
    double reward = this->env.Sample(currentS, mlAction, nextS);

    if (std::abs(nextS.Data()[2]) > 0.21 || std::abs(nextS.Data()[0]) > 2.4) {
        reward = -100.0;
    } else {
        reward = 1.0;
    }

    int toState = Discretizer::getDiscreteState(params.limits, nextS.Data(), params.bins);
    double maxNextQ = std::max(Q->at(toState, 0), Q->at(toState, 1));

    double alpha = 0.1;
    double currentQ = Q->at(fromState, actionIdx);
    Q->at(fromState, actionIdx) = currentQ + alpha * (reward + this->gamma * maxNextQ - currentQ);

    currentS = nextS;
}

void Agent::init() {
    brain.Add<mlpack::Linear>(64);
    brain.Add<mlpack::ReLU>();

    brain.Add<mlpack::Linear>(32);
    brain.Add<mlpack::ReLU>();

    brain.Add<mlpack::Linear>(1);
    brain.Add<mlpack::Sigmoid>();
}

void Agent::trainFromSupervisor(int numSamples) {
    arma::mat states(4, numSamples);
    arma::mat targets(1, numSamples);

    std::uniform_real_distribution<double> distPos(-1.5, 1.5);
    std::uniform_real_distribution<double> distVelo(-1.0, 1.0);
    std::uniform_real_distribution<double> distAngle(-0.15, 0.15);
    std::uniform_real_distribution<double> distOmega(-1.0, 1.0);

    int count0 = 0;
    int count1 = 0;

    std::cout << "Generating Symetric data for neural network..." << std::endl;

    for (int i = 0; i < numSamples; ++i) {
        arma::vec s = { distPos(rng), distVelo(rng), distAngle(rng), distOmega(rng) };

        bool mirror = (i % 2 == 1);
        if (mirror) {
            s = -s;
        }

        int stateIdx = Discretizer::getDiscreteState(params.limits, s, params.bins);
        double bestAction = (Q->at(stateIdx, 0) >= Q->at(stateIdx, 1)) ? 0.0 : 1.0;

        if (mirror) {
            bestAction = (bestAction == 0.0) ? 1.0 : 0.0;
        }

        if (bestAction == 0.0) count0++; else count1++;

        states.col(i) = s;
        targets.col(i) = bestAction;
    }

    std::cout << "DEBUG: Division of actions: 0: " << count0 << ", 1: " << count1 << std::endl;

    std::cout << "Training neural network (100 epoch)..." << std::endl;
    for (int epoch = 1; epoch <= 100; ++epoch) {
        brain.Train(states, targets);
        if (epoch % 10 == 0) std::cout << "Epoch " << epoch << "/100..." << std::endl;
    }
    std::cout << "Done!" << std::endl;
}