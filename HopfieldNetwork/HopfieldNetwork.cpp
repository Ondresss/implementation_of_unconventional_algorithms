//
// Created by andrew on 08.03.26.
//

#include "HopfieldNetwork.h"

#include <stdexcept>

void HopfieldNetwork::train() {
    if (this->patterns.empty()) throw std::runtime_error("Pattern not found");
    std::size_t N = this->patterns.at(0).numOfPixels();
    this->W = std::make_shared<Matrix<int32_t>>(N,N);
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
