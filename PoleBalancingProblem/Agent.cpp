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
    for (int i = 0; i < numSamples; ++i) {
        arma::vec s = { distPos(rng), distVelo(rng), distAngle(rng), distOmega(rng) };

        bool mirror = (i % 2 == 1);
        if (mirror) s = -s;

        arma::vec s_norm = s;
        s_norm[0] /= 2.4; s_norm[1] /= 3.0; s_norm[2] /= 0.21; s_norm[3] /= 4.0;

        int stateIdx = Discretizer::getDiscreteState(params.limits, s, params.bins);

        double bestAction = (Q->at(stateIdx, 0) >= Q->at(stateIdx, 1)) ? 0.0 : 1.0;

        if (mirror) {
            bestAction = (bestAction == 0.0) ? 1.0 : 0.0;
        }

        states.col(i) = s_norm;
        targets.col(i) = bestAction;
    }

    for (int epoch = 1; epoch <= 200; ++epoch) {
        std::cout << "Epoch: " << epoch << std::endl;
        brain.Train(states, targets);
    }
}