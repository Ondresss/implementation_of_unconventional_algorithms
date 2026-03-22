//
// Created by andrew on 3/22/26.
//
#pragma once
#include <mlpack/core.hpp>
#include <mlpack/methods/reinforcement_learning/environment/cart_pole.hpp>
class Discretizer {
public:
    static int getDiscreteState(const std::vector<std::tuple<double,double>>& limits, const arma::vec& s, int noBins) {
        int iX     = calculateBin(s[0], std::get<0>(limits[0]), std::get<1>(limits[0]), noBins);
        int iV     = calculateBin(s[1], std::get<0>(limits[1]), std::get<1>(limits[1]), noBins);
        int iTheta = calculateBin(s[2], std::get<0>(limits[2]), std::get<1>(limits[2]), noBins);
        int iOmega = calculateBin(s[3], std::get<0>(limits[3]), std::get<1>(limits[3]), noBins);

        return iX + noBins * (iV + noBins * (iTheta + noBins * iOmega));
    }

    static int calculateBin(double val, double min, double max, int noBins) {
        if (val <= min) return 0;
        if (val >= max) return noBins - 1;
        return static_cast<int>(((val - min) / (max - min)) * noBins);
    }
};