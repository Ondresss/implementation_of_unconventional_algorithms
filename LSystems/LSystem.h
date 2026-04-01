//
// Created by andrew on 3/29/26.
//
#pragma once
#include <memory>
#include <stack>
#include <string>

#include "IDrawable.h"
#include "Turtle.h"

class LSystem {
public:
    struct Rule {
        char toReplace;
        std::string rule;
    };
    LSystem(std::string text_,Rule rule_,float rotationAngle_,int step_)
    : text(std::move(text_)), rule(std::move(rule_))
    ,turtle(std::make_unique<Turtle>(Vector2{5,5}))
    ,rotationAngle(rotationAngle_)
    ,step(step_) {}
    void run(int noIter);
    void draw();
private:
    std::string text;
    Rule rule{};
    std::unique_ptr<Turtle> turtle;
    float rotationAngle = 0.0f;
    int step = 5;
    std::stack<Turtle> st;
};

