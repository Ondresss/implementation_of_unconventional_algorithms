//
// Created by andrew on 3/16/26.
//

#include "QLearningVisualizer.h"

#include <iostream>
#include <ostream>

void QLearningVisualizer::setup() {
    this->agent->generateRandomValidPosition();
    this->currentStart = this->agent->getCurrentStart();
    this->currentPath = this->agent->getBestPath(this->currentStart.first);
}

void QLearningVisualizer::visualizePath(const Rectangle& rec) {
    if (this->currentPathIndex < this->currentPath.size()) {
        std::cout << "Yess" << std::endl;
        std::cout << this->currentPath.size() << std::endl;
        int nextRoom = this->currentPath.at(this->currentPathIndex);

        this->agent->setAgentPosition(nextRoom, nextRoom);
        this->currentPathIndex++;
    }

    this->agent->draw(rec);

    this->agent->drawPathOverlay(rec, this->currentPath);
}

bool QLearningVisualizer::shouldStop() {
    if (this->currentIteration >= this->noIterations ) {
        this->currentIteration = 0;
        this->currentPath = this->agent->getBestPath(this->currentStart.first);
        return true;
    }
    return false;
}

bool QLearningVisualizer::visualizePathStop() {
    if (this->currentPathIndex >= this->currentPath.size()) {
        this->currentPathIndex = 0;
        return true;
    }
    return false;
}


void QLearningVisualizer::visualize(const Rectangle& rec) {
    this->agent->nextStep();
    this->currentIteration++;
    std::string iterationStr = "iteration: " + std::to_string(this->currentIteration);
    DrawText(iterationStr.c_str(),rec.x - rec.width * 0.35,rec.y + rec.height * 0.8,32,BLACK);
    this->agent->draw(rec);
}

void QLearningVisualizer::visualizeStart(const Rectangle& rec) {
    this->agent->draw(rec);
}
