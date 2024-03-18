#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include <vector>
#define PI 3.14159265359
#define P2 PI / 2
#define P3 3 * PI / 2
#define DR 0.0174533 // one degree in radians

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

float px = 300, py = 300; // player pos
float pdx, pdy, pa;       // delta x, y, angle
SDL_Rect player;

int mapX = 8, mapY = 8, mapS = 64;

int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1};

void drawMap2D(SDL_Renderer *renderer)
{
    int x, y, xo, yo; // x,y and offsets to account for size
    for (int y = 0; y < mapY; y++)
    {
        for (int x = 0; x < mapX; x++)
        {
            xo = x * mapS;
            yo = y * mapS;
            if (map[y * mapX + x] == 1)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
            else
                SDL_SetRenderDrawColor(renderer, 1, 1, 1, 1);
            SDL_Rect mapTile = spriteRect(xo + 1, yo + 1, mapS - 1, mapS - 1); // +1 & -1 to add the outline to our rectangles
            SDL_RenderFillRect(renderer, &mapTile);
        }
    }
}

float dist(float ax, float ay, float bx, float by, float ang)
{
    return (sqrt(bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}

float degToRad(int a) { return a * M_PI / 180.0; }

int FixAng(int a)
{
    if (a > 359)
    {
        a -= 360;
    }
    if (a < 0)
    {
        a += 360;
    }
    return a;
}

void drawRays2D(SDL_Renderer *renderer)
{

    int r, mx, my, mp, dof, side;
    float vx, vy, rx, ry, ra, xo, yo, disV, disH;
    // SDL_Rect rect = {0, 0, 1006 - 526, 160};
    SDL_Rect rect = {0, 0, 1024, 350};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
    SDL_RenderFillRect(renderer, &rect);
    // rect = {0, 160, 1006 - 526, 320 - 160};
    rect = {0, 350, 1024, 512 - 350};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 1);
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

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disH = disV;
            SDL_SetRenderDrawColor(renderer, 80, 0, 0, 1);
        } // horizontal hit first
        // SDL_RenderDrawLineF(renderer, px, py, rx, ry);

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

void movement()
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_W])
    {
        py += pdy * 1.5;
        px += pdx * 1.5;
    }
    if (keyState[SDL_SCANCODE_A])
    {
        pa += 1.5;
        pa = FixAng(pa);
        pdx = cos(degToRad(pa));
        pdy = -sin(degToRad(pa));
    }
    if (keyState[SDL_SCANCODE_D])
    {
        pa -= 1.5;
        pa = FixAng(pa);
        pdx = cos(degToRad(pa));
        pdy = -sin(degToRad(pa));
    }
    if (keyState[SDL_SCANCODE_S])
    {
        py -= pdy * 1.5;
        px -= pdx * 1.5;
    }

    player.x = px;
    player.y = py;
}

int main(int argc, char *argvs[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        printf("SDL Init error, SDL_Error: ", SDL_GetError());

    window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SC_WIDTH, SC_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
        printf("SDL Window error, SDL_Error: ", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        printf("SDL Renderer error, SDL_Error: ", SDL_GetError());

    player.x = px;
    player.y = py;
    player.w = 15;
    player.h = 15;
    pdx = cos(pa) * 5;
    pdy = sin(pa) * 5;

    SDL_Event e;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            }
        }

        movement();

        SDL_RenderClear(renderer);

        // drawMap2D(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 1);
        // SDL_RenderFillRect(renderer, &player);
        // SDL_RenderDrawLine(renderer, px, py, px + pdx * 20, py + pdy * 20);
        drawRays2D(renderer);

        SDL_SetRenderDrawColor(renderer, 70, 70, 70, 1);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}