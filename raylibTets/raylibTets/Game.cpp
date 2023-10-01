#include <iostream>
#include "Player.h"

int Run(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Platformer");

    Player player;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //updates
        player.move();
        BeginDrawing();
        //draws
        ClearBackground(RAYWHITE);
        player.draw();


        EndDrawing();
    }

    CloseWindow();

    return 0;
}
