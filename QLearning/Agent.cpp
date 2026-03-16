//
// Created by andrew on 3/16/26.
//

#include "Agent.h"
#include <iostream>

void Agent::generateRandomValidPosition() {
    std::uniform_int_distribution<int> randomRow(0,this->R->rows-1);
    while (true) {
        int generatedRow = randomRow(this->rng);
        for (int column = 0; column < this->R->rows; column++) {
            if (this->R->at(generatedRow, column) != -1) {
                this->agentStart = {generatedRow, column} ;
                return;
            }
        }
    }

}

void Agent::draw(const Rectangle& rec) {
    int mazeSize = 6;
    float cellW = rec.width / mazeSize;
    float cellH = rec.height / mazeSize;

    for (int y = 0; y < mazeSize; y++) {
        for (int x = 0; x < mazeSize; x++) {
            int currentState = y * mazeSize + x;
            Rectangle cell = { rec.x + x * cellW, rec.y + y * cellH, cellW, cellH };

            bool isWall = true;
            double maxQ = -1.0;

            for (int next = 0; next < this->Q->cols; next++) {
                if (this->R->at(currentState, next) != -1) isWall = false;
                if (this->Q->at(currentState, next) > maxQ) maxQ = this->Q->at(currentState, next);
            }

            if (currentState == 35) {
                DrawRectangleRec(cell, WHITE);

                Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(this->targetTexture.width), static_cast<float>(this->targetTexture.height) };
                DrawTexturePro(this->targetTexture, sourceRec, cell, {0,0}, 0.0f, WHITE);

            } else if (isWall) {
                Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(this->wallTexture.width), static_cast<float>(this->wallTexture.height) };

                DrawTexturePro(this->wallTexture, sourceRec, cell, {0,0}, 0.0f, WHITE);

            }else {
                DrawRectangleRec(cell, WHITE);

                if (maxQ > 0) {
                    unsigned char green = (unsigned char)std::min(255.0, (maxQ / 100.0) * 255.0);
                    DrawRectangleRec(cell, { 50, green, 50, 180 });
                }
            }

            DrawRectangleLinesEx(cell, 1.0f, GRAY);
        }
    }

    int currentPos = this->agentStart.first;
    int ay = currentPos / mazeSize;
    int ax = currentPos % mazeSize;

    Rectangle agentCell = {
        rec.x + ax * cellW,
        rec.y + ay * cellH,
        cellW,
        cellH
    };

    Rectangle sourceRec = {
        0.0f,
        0.0f,
        static_cast<float>(this->agentTexture.width),
        static_cast<float>(this->agentTexture.height)
    };

    DrawTexturePro(this->agentTexture, sourceRec, agentCell, {0, 0}, 0.0f, WHITE);

}

void Agent::setAgentPosition(int r, int c) {
    this->agentStart = {r, c};
}
void Agent::drawPathOverlay(const Rectangle& rec, const std::vector<int>& path) {
    if (path.empty()) return;

    int mazeSize = 6;
    float cellW = rec.width / mazeSize;
    float cellH = rec.height / mazeSize;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        int x1 = path[i] % mazeSize;
        int y1 = path[i] / mazeSize;
        int x2 = path[i+1] % mazeSize;
        int y2 = path[i+1] / mazeSize;

        Vector2 start = {
            rec.x + x1 * cellW + cellW/2,
            rec.y + y1 * cellH + cellH/2
        };
        Vector2 end = {
            rec.x + x2 * cellW + cellW/2,
            rec.y + y2 * cellH + cellH/2
        };

        DrawLineEx(start, end, 5.0f, RED);
        DrawCircleV(end, 5.0f, RED);
    }
}


bool Agent::shouldStop() {
    return this->stop;
}
std::vector<int> Agent::getBestPath(int startRoom) {
    std::vector<int> path;
    int current = startRoom;
    path.push_back(current);


    int maxSteps = 100;
    while (current != 35 && maxSteps-- > 0) {
        int bestNextRoom = -1;
        double maxQ = 0.000001;
        for (int c = 0; c < Q->cols; ++c) {
            if (Q->at(current, c) > maxQ) {
                maxQ = Q->at(current, c);
                bestNextRoom = c;
            }
        }
        if (bestNextRoom == -1) {
            break;
        }
        current = bestNextRoom;
        path.push_back(current);
    }

    if (current == 35) std::cout << "DEBUG: Cil nalezen! Delka cesty: " << path.size() << std::endl;
    return path;
}
void Agent::nextStep() {
    this->stop = false;

    if (this->agentStart.first != this->agentStart.second) {
        this->agentStart.first = this->agentStart.second;
        return;
    }

    int fromState = this->agentStart.first;

    std::uniform_int_distribution<int> randomCol(0, this->R->cols - 1);
    int toState = randomCol(this->rng);
    while (this->R->at(fromState, toState) == -1) {
        toState = randomCol(this->rng);
    }

    double maxVal = 0;
    for (int col = 0; col < this->Q->cols; col++) {
        if (this->Q->at(toState, col) > maxVal) maxVal = this->Q->at(toState, col);
    }

    *this->lastQ = *this->Q;
    double reward = this->R->at(fromState, toState);
    this->Q->at(fromState, toState) = reward + this->gamma * maxVal;

    this->agentStart = { fromState, toState };
}