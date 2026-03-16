//
// Created by andrew on 3/16/26.
//

#pragma once
#include <raylib.h>
class IVisualizable {
public:
    virtual ~IVisualizable() = default;
    virtual void visualize(const Rectangle& rec) = 0;
    virtual void visualizeStart(const Rectangle& rec) = 0;
    virtual void visualizePath(const Rectangle& rec) = 0;
    virtual void setup() = 0;
    virtual bool shouldStop() = 0;
};