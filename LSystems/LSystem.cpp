//
// Created by andrew on 3/29/26.
//

#include "LSystem.h"

void LSystem::run(int noIter) {
    std::string buffer;
    for (int i = 0; i < noIter; ++i) {
        buffer.reserve(this->text.length() * 2);
        for (char c : this->text) {
            if (c == this->rule.toReplace) {
                buffer.append(this->rule.rule);
            } else {
                buffer.push_back(c);
            }
        }
        this->text = buffer;
        buffer.clear();
    }
}
void LSystem::draw() {
    turtle->setState({static_cast<float>(GetScreenWidth() * 0.6), (float)GetScreenHeight() - 50}, -PI/2.0f);

    for (char c : text) {
        if (c == 'F') {
            Vector2 oldPos = turtle->getPosition();
            float currAngle = turtle->getAngle();

            Vector2 nextPos = {
                oldPos.x + std::cos(currAngle) * static_cast<float>(step),
                oldPos.y + std::sin(currAngle) * static_cast<float>(step)
            };

            turtle->setState(nextPos, currAngle);
            turtle->draw();
        }
        else if (c == '+') {
            turtle->setState(turtle->getPosition(), turtle->getAngle() + rotationAngle);
        }
        else if (c == '-') {
            turtle->setState(turtle->getPosition(), turtle->getAngle() - rotationAngle);
        }
        else if (c == '[') {
            st.push(*turtle);
        }
        else if (c == ']') {
            if (!st.empty()) {
                *turtle = st.top();
                st.pop();
                turtle->resetLastPos();
            }
        }
    }
}