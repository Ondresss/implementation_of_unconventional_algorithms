//
// Created by andrew on 08.03.26.
//

#pragma once
#include <memory>

#include "Picture.h"
#include "Matrix.h"
class HopfieldNetwork {
public:
    explicit HopfieldNetwork(std::vector<Picture> patterns) : patterns(std::move(patterns)) {} ;
    void train();
private:
    std::vector<Picture> patterns;
    std::shared_ptr<Matrix<int32_t>> W = nullptr;
};

