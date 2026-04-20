#include "Agent.h"
#include <iostream>

void Agent::nextStep(mlpack::CartPole::State& currentS) {
    static int totalSteps = 0;
    totalSteps++;

    double epsilon = std::max(0.01, 1.0 - (totalSteps / 500000.0));

    int fromState = Discretizer::getDiscreteState(params.limits, currentS.Data(), params.bins);
    int actionIdx;

    std::uniform_real_distribution<double> dist(0.0, 1.0);
    if (dist(rng) < epsilon) {
        actionIdx = std::uniform_int_distribution<int>(0, 1)(this->rng);
    } else {
        actionIdx = (Q->at(fromState, 0) >= Q->at(fromState, 1)) ? 0 : 1;
    }

    mlpack::CartPole::Action mlAction;
    mlAction.action = (actionIdx == 0) ? mlpack::CartPole::Action::backward : mlpack::CartPole::Action::forward;

    mlpack::CartPole::State nextS;
    double reward = this->env.Sample(currentS, mlAction, nextS);

    bool isDone = (std::abs(nextS.Data()[2]) > 0.21 || std::abs(nextS.Data()[0]) > 2.4);
    if (isDone) reward = -100.0;
    else reward = 1.0;

    int toState = Discretizer::getDiscreteState(params.limits, nextS.Data(), params.bins);
    double maxNextQ = std::max(Q->at(toState, 0), Q->at(toState, 1));

    double alpha = 0.1;
    double currentQ = Q->at(fromState, actionIdx);

    double target;
    if (isDone) {
        target = reward;
    } else {
        target = reward + this->gamma * maxNextQ;
    }

    Q->at(fromState, actionIdx) = currentQ + alpha * (target - currentQ);

    if (isDone) {
        mlpack::CartPole::State resetState;
        mlpack::CartPole::Action dummy;
        dummy.action = mlpack::CartPole::Action::backward;
        env.Sample(resetState, dummy, currentS);
    } else {
        currentS = nextS;
    }
}
void Agent::init() {
    brain = mlpack::FFN<mlpack::MeanSquaredError>();

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

    std::cout << "\nGeneruji " << numSamples << " expertnich vzorku z nahrane Q-tabulky..." << std::endl;

    mlpack::CartPole::State simState;
    mlpack::CartPole::Action dummyAction;
    dummyAction.action = mlpack::CartPole::Action::backward;
    env.Sample(mlpack::CartPole::State(), dummyAction, simState);

    int collected = 0;
    while (collected < numSamples) {
        int stateIdx = Discretizer::getDiscreteState(params.limits, simState.Data(), params.bins);

        int actionIdx = (Q->at(stateIdx, 0) >= Q->at(stateIdx, 1)) ? 0 : 1;

        arma::vec s_norm = simState.Data();
        s_norm[0] /= 2.4;
        s_norm[1] /= 3.0;
        s_norm[2] /= 0.21;
        s_norm[3] /= 4.0;

        states.col(collected) = s_norm;
        targets.col(collected) = static_cast<double>(actionIdx);
        collected++;

        mlpack::CartPole::Action mlAction;
        mlAction.action = (actionIdx == 0) ? mlpack::CartPole::Action::backward : mlpack::CartPole::Action::forward;

        mlpack::CartPole::State nextS;
        env.Sample(simState, mlAction, nextS);

        if (std::abs(nextS.Data()[2]) > 0.21 || std::abs(nextS.Data()[0]) > 2.4) {
            env.Sample(mlpack::CartPole::State(), dummyAction, simState); // Reset
        } else {
            simState = nextS;
        }
    }

    std::cout << "Data nasbirana. Zahajuji trenink neuronove site..." << std::endl;

    for (int epoch = 1; epoch <= 100; ++epoch) {
        brain.Train(states, targets);
        if (epoch % 10 == 0) {
            std::cout << "Epoch: " << epoch << " / 100\r" << std::flush;
        }
    }
    std::cout << "\nTrening site dokoncen!" << std::endl;
}