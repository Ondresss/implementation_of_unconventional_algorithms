//
// Created by andrew on 08.03.26.
//

#pragma once
#include <memory>

#include "Picture.h"
#include "Matrix.h"
#include "IFunction.h"
#include <random>
class HopfieldNetwork {
public:
    HopfieldNetwork(std::vector<Picture> patterns,std::shared_ptr<IFunction> f)
    : patterns(std::move(patterns)), activationFunction(f) {} ;
    void train();
    void recover(Picture& pic,int maxIter);
    double calculateEnergy(Picture& pic);
private:
    std::vector<Picture> patterns;
    std::shared_ptr<HopField::Matrix<int32_t>> W = nullptr;
    std::shared_ptr<IFunction> activationFunction = nullptr;
};

