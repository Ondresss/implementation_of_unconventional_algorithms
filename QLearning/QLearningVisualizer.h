//
// Created by andrew on 3/16/26.
//
#pragma once
#include  "Agent.h"
#include "IVisualizable.h"

class QLearningVisualizer final : public IVisualizable {
public:
    QLearningVisualizer(std::shared_ptr<Agent> agent_,int noIterations_)
    : agent(std::move(agent_)), noIterations(noIterations_) {};

    void visualize(const Rectangle& rec) override;
    void visualizeStart(const Rectangle& rec) override;
    void visualizePath(const Rectangle& rec) override;
    bool shouldStop() override;
    bool visualizePathStop();
    void setup() override;
private:
    std::shared_ptr<Agent> agent = nullptr;
    int noIterations = 0;
    int currentIteration = 0;
    std::vector<int> currentPath;
    std::pair<int,int> currentStart;
    int currentPathIndex = 0;
};

