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

void rEngine::drawRays2D(SDL_Renderer *renderer, int px, int py, int pa, int mapX, int mapY, int mapS, int mapW[], int textures[], int mapF[], int mapC[])
{
    int r, mx, my, mp, dof, side;
    float vx, vy, rx, ry, ra, xo, yo, disV, disH;

    ra = FixAng(pa + 30);

    for (r = 0; r < 60; r++)
    {

        int vmt = 0, hmt = 0;

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
            if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0)
            {
                vmt = mapW[mp] - 1;
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
            if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0)
            {
                hmt = mapW[mp] - 1;
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

        float shade = 1;
        SDL_SetRenderDrawColor(renderer, wr, wg, wb, wa);
        if (disV < disH)
        {
            hmt = vmt;
            shade = 0.5;
            rx = vx;
            ry = vy;
            disH = disV;
            SDL_SetRenderDrawColor(renderer, swr, swg, swb, swa);
        } // horizontal hit first

        int ca = FixAng(pa - ra);
        disH = disH * cos(degToRad(ca)); // fix fisheye
        int lineH = (mapS * 640) / (disH);
        float ty_step = 32.0 / (float)lineH;
        float ty_off = 0;
        if (lineH > 640)
        {
            ty_off = (lineH - 640) / 2.0;
            lineH = 640;
        }                                 // line height and limit
        int lineOff = 320 - (lineH >> 1); // line offset

        // draws walls
        int y = 0;
        float ty = ty_off * ty_step + hmt * 32;
        float tx;
        if (shade == 1)
        {
            tx = (int)(rx / 2.0) % 32;
            if (ra > 180)
                tx = 31 - tx;
        }
        else
        {
            tx = (int)(ry / 2.0) % 32;
            if (ra > 90 && ra < 270)
                tx = 31 - tx;
        }

        for (y = 0; y < lineH; y++)
        {
            SDL_RenderSetScale(renderer, 20, 1);
            float c = textures[(int)ty * 32 + (int)(tx)] * shade;
            c *= 255;
            if (hmt == 0)
                SDL_SetRenderDrawColor(renderer, c, c / 2.0, c / 2.0, 1);
            if (hmt == 1)
                SDL_SetRenderDrawColor(renderer, c, c, c / 2.0, 1);
            if (hmt == 2)
                SDL_SetRenderDrawColor(renderer, c / 2.0, c / 2.0, c, 1);
            if (hmt == 3)
                SDL_SetRenderDrawColor(renderer, c / 2.0, c, c / 2.0, 1);
            SDL_RenderDrawPoint(renderer, r * 18 / 18, y + lineOff / 1);
            ty += ty_step;
            SDL_SetRenderDrawColor(renderer, c, c, c, 1);
        }
        // draw floors
        for (y = lineOff + lineH; y < 640; y++)
        {
            float dy = y - (640 / 2.0), deg = degToRad(ra), raFix = cos(degToRad(FixAng(pa - ra)));
            tx = px / 2 + cos(deg) * 158 * 32 / dy / raFix;
            ty = py / 2 - sin(deg) * 158 * 32 / dy / raFix;
            int mp = mapF[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32;
            float c = textures[((int)(ty) & 31) * 32 + ((int)(tx) & 31) + mp] * 178;
            SDL_SetRenderDrawColor(renderer, c / 1.3, c / 1.3, c, 1);
            SDL_RenderDrawPoint(renderer, r * 18 / 18, y / 1);

            // draw ceiling
            mp = mapC[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32;
            c = textures[((int)(ty) & 31) * 32 + ((int)(tx) & 31) + mp] * 178;
            SDL_SetRenderDrawColor(renderer, c / 2.0, c / 1.2, c / 2.0, 1);
            SDL_RenderDrawPoint(renderer, r * 18 / 18, 640 - y / 1);
        }

        ra = FixAng(ra - 1); // go to next ray, 60 total
        SDL_RenderSetScale(renderer, 1, 1);
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
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        printf("SDL Renderer error, SDL_Error: ", SDL_GetError());
    return renderer;
}
