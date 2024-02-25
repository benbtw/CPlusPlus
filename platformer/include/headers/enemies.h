#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <iostream>

class Enemy
{
private:
    SDL_Texture *enemy;
    std::vector<SDL_Rect> positions;
    SDL_Rect rightAnim[6];
    SDL_Rect leftAnim[6];
    SDL_Rect test;
    int delay, index;
    char direction;
    SDL_Point velocity;
    int speed;
    int maxDist;
    int steps;

public:
    void init(SDL_Renderer *renderer);
    void update(float dt, SDL_Rect &playerBox, bool &death);
    void draw(SDL_Renderer *renderer, SDL_Rect cameraRect);
    ~Enemy();
};