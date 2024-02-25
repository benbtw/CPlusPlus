#include <stdio.h>
#include <stdlib.h>
#include <gems.h>
#include <player.h>
#include <world.h>
#include <enemies.h>
#include <menus.h>

const int SC_WIDTH = 1024;
const int SC_HEIGHT = 512;

void reset(SDL_Renderer *renderer, Player &p, World &w, Gem &g, Enemy &e);

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

    SDL_Event event;
    bool running = true;

    Player p;
    World w;
    Gem g;
    Enemy e;
    Menu m;

    w.loadMapFile();
    g.init(renderer);
    p.init(renderer);
    w.init(renderer);
    e.init(renderer);
    m.init(renderer);

    while (running)
    {
        frameStart = SDL_GetTicks();

        float dt = frameStart - frameTime;

        if (dt > 0.15)
            dt = 0.15;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            if (SDL_KEYDOWN == event.type)
            {
                if (SDLK_r == event.key.keysym.sym && p.death)
                    reset(renderer, p, w, g, e);
                if ((SDLK_e == event.key.keysym.sym && p.death) || (SDLK_e == event.key.keysym.sym && m.start))
                    running = false;
                if (SDLK_p == event.key.keysym.sym && m.start)
                {
                    reset(renderer, p, w, g, e);
                    m.start = false;
                }
            }
        }

        if (m.start)
        {
            m.mainMenu(renderer);
        }
        else
        {
            cameraRect.x = p.getPosX() - 512;
            cameraRect.y = p.getPosY() - 256;

            if (cameraRect.x < 0)
                cameraRect.x = 0;
            if (cameraRect.y < 0)
                cameraRect.y = 0;

            if (cameraRect.x + cameraRect.w >= 4320)
                cameraRect.x = 4320 - 1024;
            if (cameraRect.y + cameraRect.h >= 910)
                cameraRect.y = 910 - 430;

            p.update(w.colTiles, cameraRect, dt);
            w.update(p.playerBox, p.death);
            g.update(p.playerBox);
            e.update(dt, p.playerBox, p.death);

            if (p.death)
                m.deathMenu(renderer);
            else if (g.gemCount == 14)
                m.winMenu(renderer);
            else
            {
                SDL_RenderClear(renderer);
                w.draw(renderer, cameraRect.x, cameraRect.y);
                g.draw(renderer, cameraRect);
                e.draw(renderer, cameraRect);
                p.draw(renderer, cameraRect);
                m.gemCounter(renderer, g.gemCount);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
                SDL_RenderPresent(renderer);
            }
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}

void reset(SDL_Renderer *renderer, Player &p, World &w, Gem &g, Enemy &e)
{
    p.init(renderer);
    w.init(renderer);
    g.init(renderer);
    e.init(renderer);
}