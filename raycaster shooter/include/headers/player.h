#pragma once
#include <SDL.h>
#include "engineUtil.h"

class Player
{
public:
    float px = 300, py = 300; // player pos
    float pdx, pdy, pa;       // delta x, y, angle
    SDL_Rect player;
    void movement();
    Player();
};