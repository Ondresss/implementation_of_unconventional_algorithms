//
// Created by andrew on 20.02.26.
//
#pragma once
#include <vector>
struct Point {
    Point(const std::vector<double>& input,int correctOutput){
        this->correctOutput = correctOutput;
        this->coordinates = input;
    }
    explicit Point(const std::vector<double>& input){
        this->coordinates = input;
    }
    std::vector<double> coordinates;
    int correctOutput = -1;
};