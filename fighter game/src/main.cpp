#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <utilities.h>

// finish character animations

const int SC_WIDTH = 1024;
const int SC_HEIGHT = 526;

int main(int argc, char *argvs[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        printf("SDL Init error, SDL_Error: ", SDL_GetError());

    window = SDL_CreateWindow("Fighter Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SC_WIDTH, SC_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
        printf("SDL Window error, SDL_Error: ", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        printf("SDL Renderer error, SDL_Error: ", SDL_GetError());

    SDL_Surface *icon = IMG_Load("res/icon.png");
    SDL_SetWindowIcon(window, icon);

    SDL_Rect playerSrc = {64, 64, 64, 64};
    SDL_Rect playerPos = {100, 100, 128, 128};
    SDL_Rect playerRec = {135, 108, 64, 110}; // x + 35, y + 8, w / 2, h - 18
    SDL_Texture *player = IMG_LoadTexture(renderer, "res/Martial Hero/Sprites/Attack2.png");

    SDL_Event e;
    bool running = true;
    int index = 0;
    int delay = 0;
    Animations a;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = false;
        }
        delay++;

        if (delay == 15)
        {
            delay = 0;
            index++;
            if (index >= 6)
                index = 0;
            playerSrc = a.attack2Anim[index];
        }
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
        SDL_RenderDrawRect(renderer, &playerRec);
        SDL_RenderCopy(renderer, player, &playerSrc, &playerPos);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(icon);
    SDL_Quit();
    return 0;
}