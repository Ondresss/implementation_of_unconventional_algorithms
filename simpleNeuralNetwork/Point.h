//
// Created by andrew on 20.02.26.
//
#pragma once
#include <vector>
struct Point {
    explicit Point(const std::vector<double>& input){
        this->coordinates = input;
    }
    std::vector<double> coordinates;
    int correctOutput = -1;
};