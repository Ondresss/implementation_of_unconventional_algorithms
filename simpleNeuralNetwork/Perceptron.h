//
// Created by andrew on 20.02.26.
//
#pragma once
#include <memory>
#include <random>
#include <vector>

#include "Point.h"
#include "IFunction.h"
#include <matplot/matplot.h>
class Perceptron final {
public:
    explicit Perceptron(std::shared_ptr<IFunction> f_) : f(std::move(f_)),rng(std::random_device {}()) {};
    double run(Point& p) const;
    [[nodiscard]] double getLastSum() const { return this->lastSum; };
    void recalculateWeights(double delta,const std::vector<double>& inputs);
    [[nodiscard]] const std::vector<double>& getWeights() const { return this->weights; };
    [[nodiscard]] double getLastSumDerivative() const {return this->f->derivative(this->lastSum);};
    void generateRandomParameters(int dim);
private:
    std::shared_ptr<IFunction> f;
    std::vector<double> weights;
    double offset = -1;
    std::mt19937 rng;
    double lastSum = -1;

};

