//
// Created by andrew on 4/8/26.
//

#pragma once
#include <memory>
#include <random>
#include <matplot/matplot.h>

#include "IVisualizable.h"
#include "Matrix.h"
class IFS : public IVisualizable {
public:
    struct Point {
        std::vector<double> coords;
    };
    struct Transformation {
        IFSUTILS::Matrix<double> transformation;
        Point translation;
    };
    IFS(Point point);
    void run(int no_iter);
    void visualize() override;
private:
    std::vector<Transformation> transformations;
    std::vector<Point> points;
    Point point;
    std::mt19937 rng;
};


