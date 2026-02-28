//
// Created by andrew on 28.02.26.
//

#pragma once
#include "Perceptron.h"
#include "Point.h"
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
private:
    std::vector<Point> inputLayer;
    std::vector<std::shared_ptr<Perceptron>> hiddenLayer;
    std::shared_ptr<Perceptron> outputPerceptron;
};

