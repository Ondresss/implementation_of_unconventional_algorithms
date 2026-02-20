//
// Created by andrew on 20.02.26.
//

#include "Perceptron.h"

void Perceptron::train() {
    const double learningRate = 0.1f;
    bool change = false;
    do {
        change = false;
        for (auto& point : this->pointSet->points) {
            double sum = 0.0;
            for (int i = 0; i  < point.coordinates.size(); ++i) {
                sum += point.coordinates.at(i) * this->pointSet->weights.at(i);
            }
            sum += this->pointSet->offset;
            const double res = this->f->evaluate(sum);
            double error = point.belongs - res;
            for (int i = 0; i < this->pointSet->weights.size(); ++i) {
                double lastWeight = this->pointSet->weights.at(i);
                this->pointSet->weights.at(i) = this->pointSet->weights.at(i) + error * point.coordinates.at(i) * learningRate;
                if (lastWeight != this->pointSet->weights.at(i)) {
                    change = true;
                }
            }
            double lastOffset = this->pointSet->offset;
            this->pointSet->offset += error * 1.0 * learningRate;
            if (lastOffset != this->pointSet->offset) {
                change = true;
            }
        }
    } while (change);
}

void Perceptron::predict(std::shared_ptr<PointSet> pointSet_) {
    auto points = pointSet_->points;
    for (auto point : points) {
        double sum = 0.0f;
        for (int i = 0; i < point.coordinates.size(); ++i) {
            sum += point.coordinates.at(i) * this->pointSet->weights.at(i);
        }
        sum += this->pointSet->offset;
        const double res = this->f->evaluate(sum);
        point.belongs = static_cast<int>(res);
    }
    this->predictedSet = pointSet_;
}
