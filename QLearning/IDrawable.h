//
// Created by andrew on 3/9/26.
//

#pragma once
#include <raylib.h>
class IDrawable {
public:
    virtual void draw(const Rectangle& rec) = 0;
    virtual ~IDrawable() = default;
};