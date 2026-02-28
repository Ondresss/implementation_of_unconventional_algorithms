//
// Created by andrew on 20.02.26.
//
#pragma once
#include "IFunction.h"
class Signum final : public IFunction {
public:
    double evaluate(double x) override;
    explicit Signum(std::string name_) : IFunction(std::move(name_)) {}
    [[nodiscard]] const std::string& getName() const { return name; }
};


