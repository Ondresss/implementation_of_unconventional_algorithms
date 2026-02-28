//
// Created by andrew on 20.02.26.
//

#include "Perceptron.h"


double Perceptron::run(Point& p) const {
    double sum = 0.0;
    for (int i  = 0; i < p.coordinates.size(); i++) {
        sum += p.coordinates.at(i) * this->weights.at(i);
    }
    sum += this->offset;
    return this->f->evaluate(sum);
}

void Perceptron::recalculateWeights(double delta,const std::vector<double>& inputs) {
    constexpr double learningRate = 0.1;
    for (int i  = 0; i < this->weights.size(); i++) {
        this->weights.at(i) += learningRate * delta * inputs.at(i);
    }
    this->offset += learningRate * delta;
}

void Perceptron::generateRandomParameters(int dim) {
    this->weights.clear();
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    for (int i = 0; i < dim; i++) {
        this->weights.push_back(distribution(rng));
    }
    this->offset = distribution(this->rng);
}
