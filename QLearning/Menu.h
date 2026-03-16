//
// Created by andrew on 3/9/26.
//


#include <memory>

#include "IDrawable.h"
#include "raygui.h"
#include <raylib.h>
#include "QLearningVisualizer.h"
#include <vector>
#include "IVisualizable.h"
class Menu {
public:
    Menu(std::shared_ptr<QLearningVisualizer> visualizer_)
    : visualizer(std::move(visualizer_)) {}
    void draw(const Rectangle& menuRec, const Rectangle& visualizerRec);
private:
    std::shared_ptr<QLearningVisualizer> visualizer;
    bool visualizerInitialized = false;
    bool visualizeStart = false;
    bool visualizePath = false;
};


