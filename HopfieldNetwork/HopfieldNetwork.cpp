//
// Created by andrew on 08.03.26.
//

#include "HopfieldNetwork.h"

#include <stdexcept>

void HopfieldNetwork::train() {
    if (this->patterns.empty()) throw std::runtime_error("Pattern not found");
    std::size_t N = this->patterns.at(0).numOfPixels();
    this->W = std::make_shared<HopField::Matrix<int32_t>>(N,N);
    for (auto &p : patterns) {
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                if (i != j) {
                    this->W->at(i,j) += p(i) * p(j);
                } else {
                    this->W->at(i,j) = 0;
                }
            }
        }
    }
}
void HopfieldNetwork::recover(Picture& pic, int maxIter) {
    std::size_t N = pic.numOfPixels();
    int curIter = 0;
    std::vector<int> indices(N);
    for(int i = 0; i < N; ++i) indices[i] = i;
    while (curIter < maxIter) {
        Picture oldState = pic;
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g);
        for (int i : indices) {
            double sum = 0;
            for (int j = 0; j < N; ++j) {
                sum += this->W->at(i, j) * pic(j);
            }
            double fx = this->activationFunction->evaluate(sum);
            pic(i) = fx;
        }
        if (oldState == pic) break;
        curIter++;
    }
}

double HopfieldNetwork::calculateEnergy(Picture& pic) {
    double energy = 0;
    size_t N = pic.numOfPixels();
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            energy += this->W->at(i, j) * pic(i) * pic(j);
        }
    }
    return -0.5 * energy;
}