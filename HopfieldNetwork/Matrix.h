//
// Created by andrew on 08.03.26.
//
#pragma once
#include <vector>
template <typename T>
struct Matrix {
    std::vector<T> data;
    size_t rows;
    size_t cols;
    Matrix(size_t R, size_t C) : rows(R), cols(C) {
        data.assign(R * C, T{0});
    }
    T& at(size_t r,size_t c) {
        return this->data[r * cols + c];
    }
};