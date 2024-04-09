#pragma once
#include <freeglut.h>
#include "util.h"
#include <stdio.h>

class Raycaster
{
public:
    void drawMap2D();
    void screen(int v);
    void drawRaycast(float px, float py, float pa);
};