#include <stdio.h>
#include <stdlib.h>
#include <player.h>
#include <world.h>
#include <iostream>

const int SC_WIDTH = 1024;
const int SC_HEIGHT = 512;

int main(int argc, char *argvs[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        printf("SDL Init error, SDL_Error: ", SDL_GetError());

    window = SDL_CreateWindow("Test Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SC_WIDTH, SC_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
        printf("SDL Window error, SDL_Error: ", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        printf("SDL Renderer error, SDL_Error: ", SDL_GetError());

    SDL_Rect cameraRect = {0, 0, SC_WIDTH, SC_HEIGHT};

    Uint32 frameStart;
    int frameTime;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    SDL_Event e;
    bool running = true;
    Player p;
    World w;
    w.loadMapFile();
    p.init(renderer);
    w.init(renderer);
    while (running)
    {
        frameStart = SDL_GetTicks();

        float dt = frameStart - frameTime;

        if (dt > 0.15)
            dt = 0.15;

        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            }
        }

        cameraRect.x = p.getPosX() - 512;
        cameraRect.y = p.getPosY() - 256;

        if (cameraRect.x < 0)
            cameraRect.x = 0;
        if (cameraRect.y < 0)
            cameraRect.y = 0;

        if (cameraRect.x + cameraRect.w >= 4320)
            cameraRect.x = 4320 - 1024;
        if (cameraRect.y + cameraRect.h >= 1010)
            cameraRect.y = 1010 - 430;

        p.update(w.colTiles, cameraRect, dt);

        SDL_RenderClear(renderer);
        w.draw(renderer, cameraRect.x, cameraRect.y);
        p.draw(renderer, cameraRect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
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