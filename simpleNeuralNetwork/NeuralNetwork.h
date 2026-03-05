//
// Created by andrew on 28.02.26.
//

#pragma once
#include "Perceptron.h"
#include "Point.h"
#include <iostream>
class NeuralNetwork {
public:
    NeuralNetwork(
        const std::vector<Point>& inputLayer_,
        const std::vector<std::shared_ptr<Perceptron>>& hiddenLayer_,
        std::shared_ptr<Perceptron> outputPerceptron_)
    : inputLayer(inputLayer_), hiddenLayer(hiddenLayer_), outputPerceptron(std::move(outputPerceptron_)) {}
    void init();
    void train(int maxIter);
    void test(std::vector<Point>& input) const;

    [[nodiscard]] const std::vector<std::shared_ptr<Perceptron>>& getHiddenLayer() const { return this->hiddenLayer; }
    [[nodiscard]] const std::shared_ptr<Perceptron>& getOutputPerceptron() const { return this->outputPerceptron; }


    friend std::ostream& operator<<(std::ostream& os, const NeuralNetwork& network) {
        const auto& hiddenNetworkLayer = network.getHiddenLayer();
        for (int i = 0; i < hiddenNetworkLayer.size(); ++i) {
            std::string outStr = "neuron_hidden" + std::to_string(i+1) + ".weights    ";
            os << outStr;
            const auto& weights = hiddenNetworkLayer.at(i)->getWeights();
            os << "[";
            for (int j = 0; j < weights.size(); ++j) {
                if (j == weights.size() - 1) {
                    os << weights.at(j);
                    continue;
                }
                os << weights.at(j) << ", ";
            }
            os << "]\n";
            os << "neuron_hidden" + std::to_string(i+1) + ".bias       ";
            os << hiddenNetworkLayer.at(i)->getBias();
            os << std::endl;
        }
        os << "neuron_output.weights     [";
        const auto& outputPerceptronL = network.getOutputPerceptron();
        for (int i = 0; i < outputPerceptronL->getWeights().size(); ++i) {
            os << outputPerceptronL->getWeights().at(i);
            if ( i != outputPerceptronL->getWeights().size() - 1) {
                os << ",";
            }
        }
        os << "]\n";

        os << "neuron_output.bias        " << outputPerceptronL->getBias();
        os << std::endl;

        return os;
    }
private:
    std::vector<Point> inputLayer;
    std::vector<std::shared_ptr<Perceptron>> hiddenLayer;
    std::shared_ptr<Perceptron> outputPerceptron;


};

