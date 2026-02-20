//
// Created by andrew on 20.02.26.
//
#pragma once
#include <vector>
#include "Point.h"
struct PointSet {
    std::vector<double> weights;
    double offset = -1;
    std::vector<Point> points;
};