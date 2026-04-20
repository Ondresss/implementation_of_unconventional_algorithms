//
// Created by andrew on 20.04.26.
//

#include "FractalTerrain.h"

void FractalTerrain::draw(const Line& line, int depth, int amplitude) {
    if (!depth) {
        DrawLineEx(line.start,line.end,1.0f,BLACK);
        return;
    }
    const float centerX = line.start.x + (line.end.x - line.start.x) / 2.0f;
    const int upLow = GetRandomValue(0,1);
    const float amplitudeY = upLow ? static_cast<float>(GetRandomValue(0,amplitude)) : static_cast<float>(GetRandomValue(-amplitude,0));
    float centerY = line.start.y + (line.end.y - line.start.y) / 2.0f;
    centerY += amplitudeY;

    this->draw(Line{line.start,Vector2{centerX,centerY}},depth-1,amplitude);
    this->draw(Line{Vector2{centerX,centerY},line.end},depth-1,amplitude);
}
