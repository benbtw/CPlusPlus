#pragma once
#include <freeglut.h>
#include "util.h"
#include <stdio.h>

class Player
{
public:
    float px, py, pdx, pdy, pa; // player x, y, delta x, delta y, and angle
    bool keyPickedUp;
    Player();
    void init();
    void drawPlayer2D();
    void movement();
    void ButtonDown(unsigned char key, int x, int y);
    void ButtonUp(unsigned char key, int x, int y);
};