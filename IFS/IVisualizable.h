//
// Created by andrew on 20.02.26.
//
#pragma once
class IVisualizable {
public:
    virtual ~IVisualizable() = default;
    virtual void visualize() = 0;
};