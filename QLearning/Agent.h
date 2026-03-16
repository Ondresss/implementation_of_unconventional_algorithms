//
// Created by andrew on 3/16/26.
//
#pragma once
#include "Matrix.h"
#include <cstdint>
#include <memory>
#include <random>
#include <utility>
#include "IDrawable.h"
#include <raylib.h>
#include "raygui.h"
class Agent final : public IDrawable{
public:
    Agent(double gamma_,std::shared_ptr<QLearning::Matrix<double>> R_,std::pair<int,int> targetPos_)
    : gamma(gamma_), R(std::move(R_)),rng(std::random_device{}()),targetPos(std::move(targetPos_)) {
        this->Q = std::make_shared<QLearning::Matrix<double>>(this->R->rows, this->R->cols);
        this->lastQ = this->Q;
        this->agentTexture = LoadTexture("../chicken.png");
        this->wallTexture = LoadTexture("../wall.png");
        this->targetTexture = LoadTexture("../egg.png");
    }
    void nextStep();
    void generateRandomValidPosition();
    void draw(const Rectangle& rec) override;
    bool shouldStop();
    std::vector<int> getBestPath(int startRoom);
    void setAgentPosition(int r, int c);
    void drawPathOverlay(const Rectangle& rec, const std::vector<int>& path);
    std::pair<int,int> getCurrentStart() {return this->agentStart;}
private:
    std::pair<int,int> agentStart{0,0};
    double gamma = -1;
    std::shared_ptr<QLearning::Matrix<double>> R;
    std::shared_ptr<QLearning::Matrix<double>> Q;
    std::shared_ptr<QLearning::Matrix<double>> lastQ;
    std::mt19937 rng;
    std::pair<int,int> targetPos;

    bool stop = false;
    Texture2D agentTexture;
    Texture2D wallTexture;
    Texture2D targetTexture;
};
