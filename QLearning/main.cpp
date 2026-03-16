    #include <cstdlib>
    #include <iostream>
    #include <memory>
    #include <raylib.h>
    #include "raygui.h"
    #include "Agent.h"
    #include "QLearningVisualizer.h"
    #include "Menu.h"

    int main(void) {
        const int screenWidth = 1000;
        const int screenHeight = 800;
        InitWindow(screenWidth, screenHeight, "Q-Learning Vizualizace - 2D Bludiště");
        SetTargetFPS(60);

        std::pair<int,int> targetPos{35,35};
        std::vector<std::vector<int>> maze = {
            {0, 0, 0, 0, 1, 0},
            {1, 1, 0, 1, 1, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 0},
            {0, 0, 0, 1, 0, 0},
            {1, 1, 0, 0, 0, 0}
        };

        auto R = std::make_shared<QLearning::Matrix<double>>(36, 36, -1.0);

        for (int y = 0; y < maze.size(); y++) {
            for (int x = 0; x < maze.at(y).size(); x++) {
                if (maze[y][x] == 1) continue;

                int current = y * 6 + x;
                int dx[] = {0, 0, -1, 1};
                int dy[] = {-1, 1, 0, 0};

                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (nx >= 0 && nx < 6 && ny >= 0 && ny < 6 && maze[ny][nx] == 0) {
                        int next = ny * 6 + nx;
                        R->at(current, next) = (next == 35) ? 100.0 : 0.0;
                    }
                }
            }
        }
        R->at(targetPos.first, targetPos.second) = 100.0;

        auto agent = std::make_shared<Agent>(0.8, R,targetPos);

        std::shared_ptr<QLearningVisualizer> visualizer = std::make_shared<QLearningVisualizer>(agent, 5000);

        auto menu = std::make_shared<Menu>(visualizer);


        Rectangle menuRect = { 10, 20, 250, (float)screenHeight - 40 };
        Rectangle visualizerRect = { 270, 20, (float)screenWidth - 280, (float)screenHeight - 40 };

        Color myBrown = { 245, 245, 220, 255 };

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(myBrown);

            menu->draw(menuRect, visualizerRect);

            EndDrawing();
        }

        CloseWindow();
        return EXIT_SUCCESS;
    }