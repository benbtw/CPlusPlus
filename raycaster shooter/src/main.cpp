#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include <vector>
#include <RaycastEngine.h>
#include "player.h"
#include "textures/All_Textures.ppm"

const int SC_WIDTH = 1024;
const int SC_HEIGHT = 512;

int mapX = 8, mapY = 8, mapS = 64;

int mapW[] = // walls
    {
        1, 1, 1, 1, 1, 3, 1, 1,
        1, 0, 0, 1, 0, 0, 0, 1,
        1, 0, 0, 4, 0, 2, 0, 1,
        1, 1, 4, 1, 0, 0, 0, 1,
        2, 0, 0, 0, 0, 0, 0, 1,
        2, 0, 0, 0, 0, 1, 0, 1,
        2, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 3, 1, 3, 1, 3, 1};

int mapF[] = // floors
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 0, 0,
        0, 0, 0, 0, 2, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 2, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0};

int mapC[] = // ceiling
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 1, 3, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0};

int main(int argc, char *argvs[])
{
    rEngine engine;
    Player p;

    SDL_Window *window = engine.initWindow(SC_WIDTH, SC_HEIGHT, "Raycast Shooter");
    SDL_Renderer *renderer = engine.initRenderer(window);

    Uint32 frameStart;
    int frameTime;
    const int FPS = 120;
    const int frameDelay = 1000 / FPS;

    SDL_Event e;
    bool running = true;
    while (running)
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                break;
            }
        }

        p.movement(mapW, mapX);

        SDL_RenderClear(renderer);

        engine.drawRays2D(renderer, p.px, p.py, p.pa, mapX, mapY, mapS, mapW, All_Textures, mapF, mapC);

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}