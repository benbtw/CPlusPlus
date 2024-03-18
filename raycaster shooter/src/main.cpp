#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include <vector>
#include <RaycastEngine.h>
#include "player.h"

const int SC_WIDTH = 1024;
const int SC_HEIGHT = 512;

int mapX = 8, mapY = 8, mapS = 64;

int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1};

int main(int argc, char *argvs[])
{
    rEngine engine;
    Player p;

    SDL_Window *window = engine.initWindow(SC_WIDTH, SC_HEIGHT, "Raycast Shooter");
    SDL_Renderer *renderer = engine.initRenderer(window);

    SDL_Event e;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            }
        }

        p.movement();

        SDL_RenderClear(renderer);

        engine.drawRays2D(renderer, p.px, p.py, p.pa, mapX, mapY, mapS, map);

        SDL_SetRenderDrawColor(renderer, 70, 70, 70, 1);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}