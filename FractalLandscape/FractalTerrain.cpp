//
// Created by andrew on 20.04.26.
//

#include "FractalTerrain.h"

void FractalTerrain::draw(const Line& line, int depth, float amplitude,Color color) {
    if (!depth) {
        DrawLineEx(line.start,line.end,1.0f,BLACK);
        float groundY = static_cast<float>(GetScreenHeight());

        Vector2 v1 = line.start;
        Vector2 v2 = line.end;
        Vector2 v3 = { line.end.x, groundY };
        Vector2 v4 = { line.start.x, groundY };

        DrawTriangle(v1, v3, v2, color);
        DrawTriangle(v1, v4, v3, color);
        return;
    }
    const float centerX = line.start.x + (line.end.x - line.start.x) / 2.0f;
    const int upLow = GetRandomValue(0,1);
    const float amplitudeY = upLow ?  amplitude : -amplitude;
    float centerY = line.start.y + (line.end.y - line.start.y) / 2.0f;
    centerY += amplitudeY;
    float nextAmplitude = amplitude * 0.5f;
    this->draw(Line{line.start,Vector2{centerX,centerY}},depth-1,nextAmplitude,color);
    this->draw(Line{Vector2{centerX,centerY},line.end},depth-1,nextAmplitude,color);
}
