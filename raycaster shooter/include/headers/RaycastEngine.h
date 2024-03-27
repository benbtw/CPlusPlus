#pragma once
#include <SDL.h>
#include "engineUtil.h"
#include <stdio.h>

class rEngine
{
private:
    int fr, fg, fb, fa;
    int wr, wg, wb, wa;
    int swr, swg, swb, swa;
    int cr, cg, cb, ca;

public:
    void setWallColor(int r, int g, int b, int a, int sr, int sg, int sb, int sa);
    void setFloorColor(int r, int g, int b, int a);
    void setCeilingColor(int r, int g, int b, int a);
    void drawRays2D(SDL_Renderer *renderer, int px, int py, int pa, int mapX, int mapY, int mapS, int mapW[], int textures[], int mapF[], int mapC[]);
    rEngine();
    SDL_Window *initWindow(const int screenWidth, const int screenHeight, const char *title);
    SDL_Renderer *initRenderer(SDL_Window *window);
};