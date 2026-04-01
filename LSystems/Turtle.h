//
// Created by andrew on 3/29/26.
//

#pragma once
#include <raylib.h>

#include "IDrawable.h"
#include <cmath>
class Turtle {
public:
    explicit Turtle(Vector2 dims_) : dimensions(dims_) {}
    void setState(Vector2 nextPos, float nextAngle) {
        this->lastPos = this->pos;
        this->pos = nextPos;
        this->angle = nextAngle;
    }
    Vector2& getPosition() { return this->pos; }
    [[nodiscard]] float getAngle() const { return this->angle; }
    void resetLastPos() { this->pos = this->lastPos;}
    void draw();
private:
    Vector2 pos{};
    Vector2 lastPos{};
    float angle = 0.0f;
    Vector2 dimensions{};
};


