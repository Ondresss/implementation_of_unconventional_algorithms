//
// Created by andrew on 20.02.26.
//

#include "PointLoader.h"

#include <iostream>

PointLoader::PointLoader(std::string path_) : rng(std::random_device{}()), path(std::move(path_)) {
    this->pointSet = std::make_shared<PointSet>();
}

void PointLoader::generateRandomAttributes() {
    if (this->pointSet) {
        std::uniform_real_distribution<double> randomWeights(-1.0, 1.0);
        for (int i = 0; i < this->pointSet->points.at(0).coordinates.size(); ++i) {
            this->pointSet->weights.push_back(randomWeights(rng));
        }
        this->pointSet->offset = randomWeights(rng);
    } else {
        throw std::runtime_error("PointSet is nullptr");
    }
}

void PointLoader::loadPoints() {
    std::ifstream ifs(this->path);
    if (!ifs.is_open()) throw std::runtime_error("Could not open file");
    std::vector<Point> points;
    std::string line;
    std::string pointAttr;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        Point point{};
        std::stringstream ss(line);
        std::getline(ss, pointAttr, ';');

        std::string buff;
        std::stringstream pointSS(pointAttr);
        while (std::getline(pointSS, buff, ',')) {
            point.coordinates.push_back(std::stod(buff));
        }
        for (auto coord : point.coordinates) {
            std::cout << coord << ",";
        }
        std::getline(ss, pointAttr, ';');
        std::stringstream belongSS(pointAttr);
        std::getline(belongSS, buff, ',');
        point.belongs = std::stoi(buff);
        std::cout << point.belongs << std::endl;
        points.push_back(point);
    }
    this->pointSet->points = points;
    if (this->pointSet->points.empty()) throw std::runtime_error("Could not load points, points are empty");
    this->generateRandomAttributes();
}

