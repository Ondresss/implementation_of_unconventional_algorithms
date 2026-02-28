//
// Created by andrew on 28.02.26.
//

#include "Sigmoid.h"
#include <cmath>
double Sigmoid::evaluate(double x) {
    return 1 / (1 + std::exp(-x));
}
double Sigmoid::derivative(double x) {
    const double fx = this->evaluate(x);
    return fx * (1.0 - fx);
}
