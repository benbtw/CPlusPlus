#include "RaycastEngine.h"

rEngine::rEngine()
{
    fr = 0;
    fg = 0;
    fb = 255;
    fa = 1;

    wr = 255;
    wg = 0;
    wb = 0;
    wa = 1;

    swr = 80;
    swg = 0;
    swb = 0;
    swa = 1;

    cr = 0;
    cg = 255;
    cb = 0;
    ca = 1;
}

void rEngine::drawRays2D(SDL_Renderer *renderer, int px, int py, int pa, int mapX, int mapY, int mapS, int map[])
{
    int r, mx, my, mp, dof, side;
    float vx, vy, rx, ry, ra, xo, yo, disV, disH;

    SDL_Rect rect = {0, 0, 1024, 350};
    SDL_SetRenderDrawColor(renderer, cr, cg, cb, ca);
    SDL_RenderFillRect(renderer, &rect);
    rect = {0, 350, 1024, 512 - 350};
    SDL_SetRenderDrawColor(renderer, fr, fg, fb, fa);
    SDL_RenderFillRect(renderer, &rect);

    ra = FixAng(pa + 30);

    for (r = 0; r < 60; r++)
    {
        //---Vertical---
        dof = 0;
        side = 0;
        disV = 100000;
        float Tan = tan(degToRad(ra));
        if (cos(degToRad(ra)) > 0.001)
        {
            rx = (((int)px >> 6) << 6) + 64;
            ry = (px - rx) * Tan + py;
            xo = 64;
            yo = -xo * Tan;
        } // looking left
        else if (cos(degToRad(ra)) < -0.001)
        {
            rx = (((int)px >> 6) << 6) - 0.0001;
            ry = (px - rx) * Tan + py;
            xo = -64;
            yo = -xo * Tan;
        } // looking right
        else
        {
            rx = px;
            ry = py;
            dof = 8;
        } // looking up or down. no hit

        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
            {
                dof = 8;
                disV = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py);
            } // hit
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            } // check next horizontal
        }
        vx = rx;
        vy = ry;

        //---Horizontal---
        dof = 0;
        disH = 100000;
        Tan = 1.0 / Tan;
        if (sin(degToRad(ra)) > 0.001)
        {
            ry = (((int)py >> 6) << 6) - 0.0001;
            rx = (py - ry) * Tan + px;
            yo = -64;
            xo = -yo * Tan;
        } // looking up
        else if (sin(degToRad(ra)) < -0.001)
        {
            ry = (((int)py >> 6) << 6) + 64;
            rx = (py - ry) * Tan + px;
            yo = 64;
            xo = -yo * Tan;
        } // looking down
        else
        {
            rx = px;
            ry = py;
            dof = 8;
        } // looking straight left or right

        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
            {
                dof = 8;
                disH = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py);
            } // hit
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            } // check next horizontal
        }

        SDL_SetRenderDrawColor(renderer, wr, wg, wb, wa);
        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disH = disV;
            SDL_SetRenderDrawColor(renderer, swr, swg, swb, swa);
        } // horizontal hit first

        int ca = FixAng(pa - ra);
        disH = disH * cos(degToRad(ca)); // fix fisheye
        int lineH = (mapS * 640) / (disH);
        if (lineH > 640)
        {
            lineH = 640;
        }                                 // line height and limit
        int lineOff = 320 - (lineH >> 1); // line offset

        for (int i = 0; i < 18; i++)
        {
            SDL_RenderDrawLine(renderer, r * 18 + i, lineOff, r * 18 + i, lineOff + lineH);
        }

        ra = FixAng(ra - 1); // go to next ray, 60 total
    }
}

void rEngine::setWallColor(int r, int g, int b, int a, int sr, int sg, int sb, int sa)
{
    wr = r;
    wg = g;
    wb = b;
    wa = a;
    swr = sr;
    swg = sg;
    swb = sb;
    swa = sa;
}

void rEngine::setFloorColor(int r, int g, int b, int a)
{
    fr = r;
    fg = g;
    fb = b;
    fa = a;
}

void rEngine::setCeilingColor(int r, int g, int b, int a)
{
    cr = r;
    cg = g;
    cb = b;
    ca = a;
}

SDL_Window *rEngine::initWindow(const int screenWidth, const int screenHeight, const char *title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        printf("SDL Init error, SDL_Error: ", SDL_GetError());

    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == NULL)
        printf("SDL Window error, SDL_Error: ", SDL_GetError());

    return window;
}
SDL_Renderer *rEngine::initRenderer(SDL_Window *window)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        printf("SDL Renderer error, SDL_Error: ", SDL_GetError());
    return renderer;
}
