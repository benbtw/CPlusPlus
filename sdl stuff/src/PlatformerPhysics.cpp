#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <cmath>
#include <vector>

const int SC_WIDTH = 1024;
const int SC_HEIGHT = 512;

SDL_Rect spriteRect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}

SDL_Rect player = {0, 0, 40, 56};
SDL_Rect pRect = {0, 0, 80, 80};
SDL_Point velocity = {50, 50};
SDL_Point gravity = {0, -1};
bool grounded = false;
int sum = 0;
bool left, right, top, bottom;

std::vector<SDL_Rect>
    map = {
        spriteRect(0, 448, 48, 48),
        spriteRect(48, 448, 48, 48),
        spriteRect(96, 448, 48, 48),
        spriteRect(144, 448, 48, 48),
        spriteRect(192, 448, 48, 48),
        spriteRect(240, 448, 48, 48),
        spriteRect(288, 448, 48, 48),
        spriteRect(336, 448, 48, 48),
        spriteRect(432, 448, 48, 48),
        spriteRect(480, 448, 48, 48),
        spriteRect(200, 250, 48, 48),
        spriteRect(400, 384, 48, 48)};

SDL_Rect grass = spriteRect(16, 16, 16, 16);

void drawMap(SDL_Renderer *renderer, struct SDL_Texture *world)
{
    for (int i = 0; i < map.size(); i++)
        SDL_RenderCopy(renderer, world, &grass, &map[i]);
}

bool isTouchingLeft(SDL_Rect rect)
{
    return player.x + 40 + velocity.x > rect.x &&
           player.x < rect.x &&
           player.y + 40 > rect.y &&
           player.y < rect.y + rect.h;
}

bool isTouchingRight(SDL_Rect rect)
{
    return player.x + velocity.x < rect.x + rect.w &&
           player.x + 40 > rect.x + rect.w &&
           player.y + 40 > rect.y &&
           player.y < rect.y + rect.w;
}

bool isTouchingTop(SDL_Rect rect)
{
    return player.y + 56 + velocity.y > rect.y &&
           player.y < rect.y &&
           player.x + 56 > rect.x &&
           player.x < rect.x + rect.h;
}

bool isTouchingBottom(SDL_Rect rect)
{
    return player.y + velocity.y < rect.y + rect.h &&
           player.y + 56 > rect.y + rect.h &&
           player.x + 56 > rect.x &&
           player.x < rect.x + rect.h;
}

void movement(float dt)
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    int speed = 50;
    gravity.y = -15;

    if (!grounded)
        velocity.y -= gravity.y;

    if (keyState[SDL_SCANCODE_W] && !top)
    {
        velocity.y -= speed * dt;
    }
    if (keyState[SDL_SCANCODE_A] && !left)
    {
        velocity.x -= speed * dt;
    }
    if (keyState[SDL_SCANCODE_D] && !right)
    {
        velocity.x += speed * dt;
    }
    if (keyState[SDL_SCANCODE_S] && !bottom)
    {
        velocity.y += speed * dt;
    }
    if (keyState[SDL_SCANCODE_SPACE] && grounded && !top)
    {
        velocity.y -= 15;
        gravity.y = -15;
        player.y += velocity.y * dt;
        velocity.y += gravity.y * dt;
        sum += 10;
        if (sum >= 120)
            grounded = false;
        std::cout << sum << std::endl;
    }
    else
        grounded = false;

    for (SDL_Rect tile : map)
    {
        if (velocity.x > 0 && isTouchingLeft(tile))
        {
            player.x = tile.x - tile.w + 2;
            velocity.x = 0;
            right = true;
        }
        if (velocity.x < 0 && isTouchingRight(tile))
        {
            player.x = tile.x + tile.w;
            velocity.x = 0;
            left = true;
        }
        if (velocity.y > 0 && isTouchingTop(tile))
        {
            player.y = tile.y - tile.h - 6;
            velocity.y = 0;
            bottom = true;
            grounded = true;
            sum = 0;
        }
        if (velocity.y < 0 && isTouchingBottom(tile))
        {
            player.y = tile.y + tile.h;
            velocity.y = 0;
            top = true;
        }
    }

    player.x += velocity.x;
    player.y += velocity.y;
    pRect.x = player.x - 19;
    pRect.y = player.y - 27;
    velocity.x = 0;
    velocity.y = 0;

    left = false;
    bottom = false;
    right = false;
    top = false;
}

int main(int argc, char *argvs[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        printf("SDL Init error, SDL_Error: ", SDL_GetError());

    window = SDL_CreateWindow("testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

    struct SDL_Texture *playerTex = IMG_LoadTexture(renderer, "player-idle-2.png");
    struct SDL_Texture *world = IMG_LoadTexture(renderer, "tileset.png");

    SDL_Event e;
    bool running = true;
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

        movement(dt);

        SDL_RenderClear(renderer);
        drawMap(renderer, world);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
        SDL_RenderDrawRect(renderer, &player);
        SDL_RenderCopy(renderer, playerTex, NULL, &pRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    SDL_DestroyTexture(playerTex);
    SDL_DestroyTexture(world);
    return 0;
}