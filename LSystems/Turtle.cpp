#include "Turtle.h"

void Turtle::draw() {
    float lineThickness = 2.5f;
    DrawLineEx(lastPos, pos, lineThickness, BLACK);

    float size = 3.0f;
    Vector2 v1 = { pos.x + std::cos(angle) * size, pos.y + std::sin(angle) * size };
    Vector2 v2 = { pos.x + std::cos(angle + 2.5f) * (size * 0.7f), pos.y + std::sin(angle + 2.5f) * (size * 0.7f) };
    Vector2 v3 = { pos.x + std::cos(angle - 2.5f) * (size * 0.7f), pos.y + std::sin(angle - 2.5f) * (size * 0.7f) };

    DrawTriangle(v1, v2, v3, RED);

    DrawTriangleLines(v1, v2, v3, MAROON);
}
