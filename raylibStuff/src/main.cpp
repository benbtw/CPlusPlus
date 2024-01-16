#include "raylib.h"
#include <iostream>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Texture2D player = LoadTexture("res/SpriteSheet.png");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Updates


        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(player, 100, 100, WHITE);

        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}