//
// Created by andrew on 08.03.26.
//

#include "Picture.h"

#include <complex>

void Picture::draw(const Rectangle& rec) {
    std::size_t N = std::sqrt((this->data.size()));
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            int index = r * N + c;
            Rectangle cell = {
                .x = rec.x + (c * rec.width),
                .y = rec.y + (r * rec.height),
                .width = rec.width,
                .height = rec.height
            };
            if (this->data.at(index) == 1) DrawRectangleRec(cell,BLACK);
            else DrawRectangleRec(cell,WHITE);
            DrawRectangleLinesEx(cell, 0.5f, LIGHTGRAY);
        }
    }
}
