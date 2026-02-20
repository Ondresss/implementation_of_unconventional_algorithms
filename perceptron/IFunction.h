//
// Created by andrew on 20.02.26.
//
#pragma once
#include <string>
#include "Point.h"
class IFunction {
public:
    virtual ~IFunction() = default;
    explicit IFunction(std::string name_) : name(std::move(name_)) {}
    virtual double evaluate(double x) = 0;
protected:
    std::string name;
};


