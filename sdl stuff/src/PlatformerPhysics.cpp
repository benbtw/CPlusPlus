#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
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

SDL_Rect player = {SC_WIDTH / 2, SC_HEIGHT / 2, 64, 64};
SDL_Point velocity = {50, 50};
SDL_Point gravity = {0, -1};
bool grounded = false;
int sum = 0;
bool left, right, top, bottom;

std::vector<SDL_Rect> map = {
    spriteRect(0, 448, 64, 64),
    spriteRect(64, 448, 64, 64),
    spriteRect(128, 448, 64, 64),
    spriteRect(192, 448, 64, 64),
    spriteRect(256, 448, 64, 64),
    spriteRect(320, 448, 64, 64),
    spriteRect(384, 448, 64, 64),
    spriteRect(448, 448, 64, 64),
    spriteRect(512, 448, 64, 64),
    spriteRect(576, 448, 64, 64),
    spriteRect(640, 448, 64, 64),
    spriteRect(704, 448, 64, 64),
    spriteRect(768, 448, 64, 64),
    spriteRect(832, 448, 64, 64),
    spriteRect(896, 448, 64, 64),
    spriteRect(960, 448, 64, 64),
    spriteRect(1024, 448, 64, 64),
    spriteRect(200, 250, 64, 64),
    spriteRect(400, 384, 64, 64)};

void drawMap(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
    for (int i = 0; i < map.size(); i++)
        SDL_RenderFillRect(renderer, &map[i]);
}

bool isTouchingLeft(SDL_Rect rect)
{
    return player.x + 64 + velocity.x > rect.x &&
           player.x < rect.x &&
           player.y + 64 > rect.y &&
           player.y < rect.y + 64;
}

bool isTouchingRight(SDL_Rect rect)
{
    return player.x + velocity.x < rect.x + 64 &&
           player.x + 64 > rect.x + 64 &&
           player.y + 64 > rect.y &&
           player.y < rect.y + 64;
}

bool isTouchingTop(SDL_Rect rect)
{
    return player.y + 64 + velocity.y > rect.y &&
           player.y < rect.y &&
           player.x + 64 > rect.x &&
           player.x < rect.x + 64;
}

bool isTouchingBottom(SDL_Rect rect)
{
    return player.y + velocity.y < rect.y + 64 &&
           player.y + 64 > rect.y + 64 &&
           player.x + 64 > rect.x &&
           player.x < rect.x + 64;
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
        if (sum >= 150)
            grounded = false;
        std::cout << sum << std::endl;
    }
    else
        grounded = false;

    for (SDL_Rect tile : map)
    {
        if (velocity.x > 0 && isTouchingLeft(tile))
        {
            player.x = tile.x - tile.w;
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
            player.y = tile.y - tile.h;
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
        drawMap(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
        SDL_RenderFillRect(renderer, &player);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
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