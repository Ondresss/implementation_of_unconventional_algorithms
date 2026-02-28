//
// Created by andrew on 28.02.26.
//

#pragma once

#include "IFunction.h"
class Sigmoid final : public IFunction {
public:
    double evaluate(double x) override;
    double derivative(double x) override;
    explicit Sigmoid(std::string name_) : IFunction(std::move(name_)) {}
    [[nodiscard]] const std::string& getName() const { return name; }

};


