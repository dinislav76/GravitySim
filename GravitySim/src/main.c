#include "raylib.h"
#include <stdlib.h>
#include "simulation.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "2D Gravity Simulator - ");

    SetTargetFPS(60);

    InitSimulation(screenWidth, screenHeight);

    bool paused = false;
    bool step = false;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsKeyPressed(KEY_SPACE)) paused = !paused;
        if (IsKeyPressed(KEY_S)) step = true;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 p = { (float)GetMouseX(), (float)GetMouseY() };
            Vector2 v = { 0.0f, -60.0f };
            AddBody(p, v, 8.0f, 5.0f, LIGHTGRAY);
        }

        if (!paused || step) {
            UpdateSimulation(dt);
            step = false;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawSimulation();
            DrawText("Space: Pause/Resume    S: Step    Click: Add body", 10, 10, 18, RAYWHITE);
        EndDrawing();
    }

    CloseSimulation();
    CloseWindow();
    return 0;
}