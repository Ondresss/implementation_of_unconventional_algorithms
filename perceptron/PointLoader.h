//
// Created by andrew on 20.02.26.
//
#pragma once
#include <vector>
#include <fstream>
#include <memory>
#include <random>

#include "Point.h"
#include <string>
#include <sstream>
#include "PointSet.h"
class PointLoader {
public:
    explicit PointLoader(std::string path_);
    void loadPoints();
    std::shared_ptr<PointSet> getPoints() { return this->pointSet; };
    void setPath(std::string path_) { this->path = path_; };
private:
    void generateRandomAttributes();
    std::mt19937 rng;
    std::shared_ptr<PointSet> pointSet = nullptr;
    std::string path;
};

