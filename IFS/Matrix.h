//
// Created by andrew on 08.03.26.
//
#pragma once
#include <stdexcept>
#include <vector>
namespace IFSUTILS
{
    template <typename T> struct Matrix {
        std::vector<T> data;
        size_t rows;
        size_t cols;
        Matrix(size_t R, size_t C,T s = 0) : rows(R), cols(C) {
            data.assign(R * C, s);
        }
        Matrix(size_t R, size_t C, std::initializer_list<T> list)
            : rows(R), cols(C), data(list) {
            if (list.size() != R * C) {
                throw std::runtime_error("Size of initializer list does not match Matrix dimensions!");
            }
        }
        T& at(size_t r,size_t c) {
            return this->data[r * cols + c];
        }
        static bool isNear(const Matrix<T>& a, const Matrix<T>& b, double epsilon = 0.001) {
            if (a.rows != b.rows || a.cols != b.cols) return false;

            for (size_t i = 0; i < a.data.size(); ++i) {
                if (std::abs(a.data[i] - b.data[i]) > epsilon) {
                    return false;
                }
            }
            return true;
        }
    };
}