#pragma once
#include <freeglut.h>
#include "util.h"

class Sprite
{
public:
    int type;      // static, key, enemy
    int state;     // on/off
    int map;       // which map is texture stationed to
    float x, y, z; // position
    void drawSprite(Sprite sp[], int px, int py, int pa, bool &keyPickedUp, int &gameState);
};