//
// Created by andrew on 28.02.26.
//

#include "NeuralNetwork.h"

void NeuralNetwork::init() {
    if (this->inputLayer.empty()) throw std::invalid_argument("input layer is empty");
    for (auto& perceptron : this->hiddenLayer) {
        perceptron->generateRandomParameters(static_cast<int>(this->inputLayer.at(0).coordinates.size()));
    }
    this->outputPerceptron->generateRandomParameters(static_cast<int>(this->inputLayer.at(0).coordinates.size()));
}

void NeuralNetwork::train(int maxIter) {
    double totalError = 1.0;
    int iteration = 0;
    while (totalError > 0.05 && iteration < maxIter ) {
        totalError = 0;
        for (auto& point : this->inputLayer) {
            std::vector<double> hiddenOutputs;
            for (const auto& perceptron : this->hiddenLayer) {
                hiddenOutputs.push_back(perceptron->run(point));
            }
            Point hiddenPoint(hiddenOutputs);
            double finalPrediction = this->outputPerceptron->run(hiddenPoint);
            const double error = point.correctOutput - finalPrediction;
            double outputDelta = error * this->outputPerceptron->getLastSumDerivative();

            for (int i = 0; i < this->hiddenLayer.size(); i++) {
                const double hiddenError = (outputDelta * outputPerceptron->getWeights().at(i)) * this->hiddenLayer.at(i)->getLastSumDerivative();
                this->hiddenLayer.at(i)->recalculateWeights(hiddenError, point.coordinates);
            }
            this->outputPerceptron->recalculateWeights(outputDelta, hiddenOutputs);
            totalError += std::abs(error);
            ++iteration;
        }
    }
}
void NeuralNetwork::test(std::vector<Point>& input) const {
    std::cout << "--- NEURAL NETWORK ---" << std::endl;
    for (auto& point : input) {
        std::vector<double> hiddenOutputs;
        for (auto& perceptron : this->hiddenLayer) {
            hiddenOutputs.push_back(perceptron->run(point));
        }
        Point hiddenPoint(hiddenOutputs);
        double result = this->outputPerceptron->run(hiddenPoint);
        std::cout << "Vstup: " << point.coordinates[0] << ", " << point.coordinates[1]
                  << " | Cíl: " << point.correctOutput
                  << " | AI: " << result << std::endl;
    }
}