//
// Created by andrew on 20.02.26.
//
#pragma once
#include <memory>
#include <vector>

#include "IVisualizable.h"
#include "Point.h"
#include "IFunction.h"
#include "PointSet.h"

class Perceptron final : public IVisualizable {
public:
    explicit Perceptron(std::shared_ptr<PointSet> pointSet_,std::shared_ptr<IFunction> f_) : pointSet(pointSet_),f(f_) {};
    void visualize() override {};
    void train();
    void predict(std::shared_ptr<PointSet> pointSet_);
private:
    std::shared_ptr<PointSet> pointSet = nullptr;
    std::shared_ptr<PointSet> predictedSet = nullptr;
    std::shared_ptr<IFunction> f;
};

