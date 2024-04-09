#include "raycasting.h"
#include "textures/texs.ppm"
#include "textures/won.ppm"
#include "textures/lost.ppm"

void Raycaster::drawMap2D()
{
    int x, y, xo, yo;
    for (y = 0; y < mapY; y++)
    {
        for (x = 0; x < mapX; x++)
        {
            if (mapW[y * mapX + x] > 0)
            {
                glColor3f(1, 1, 1);
            }
            else
            {
                glColor3f(0, 0, 0);
            }
            xo = x * mapS;
            yo = y * mapS;
            glBegin(GL_QUADS);
            glVertex2i(0 + xo + 1, 0 + yo + 1);
            glVertex2i(0 + xo + 1, mapS + yo - 1);
            glVertex2i(mapS + xo - 1, mapS + yo - 1);
            glVertex2i(mapS + xo - 1, 0 + yo + 1);
            glEnd();
        }
    }
}

void Raycaster::screen(int v)
{
    int x, y;
    int *T;
    if (v == 2)
        T = won;
    if (v == 3)
        T = lost;
    for (y = 0; y < 80; y++)
    {
        for (x = 0; x < 120; x++)
        {
            int pixel = (y * 120 + x) * 3;
            int red = T[pixel + 0];
            int green = T[pixel + 1];
            int blue = T[pixel + 2];
            glPointSize(8);
            glColor3ub(red, green, blue);
            glBegin(GL_POINTS);
            glVertex2i(x * 8, y * 8);
            glEnd();
        }
    }
}

void Raycaster::drawRaycast(float px, float py, float pa)
{
    int r, mx, my, mp, dof, side;                 // ray, mapX, mapY, mapPosition, depth of field, side for shading
    float vx, vy, rx, ry, ra, xo, yo, disV, disH; // vertical line X, y, ray x, y, and angle, x offset, y offset,
    // vertical and horizontal distance from wall

    ra = FixAng(pa + 30); // ray set back 30 degrees

    for (r = 0; r < 120; r++)
    {
        int vmt = 0, hmt = 0; // vertical and horizontal map texture number
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
        glColor3f(0, 0.8, 0);
        if (disV < disH)
        {
            hmt = vmt;
            shade = 0.5;
            rx = vx;
            ry = vy;
            disH = disV;
            glColor3f(0, 0.6, 0);
        } // horizontal hit first
        /*glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd(); // draw 2D ray*/

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

        depth[r] = disH;

        //---draw walls---
        int y;
        float ty = ty_off * ty_step; // texture y plus offset and step for correct textures
        float tx;
        if (shade == 1)
        {
            tx = (int)(rx / 2.0) % 32;
            if (ra > 180)
            {
                tx = 31 - tx;
            }
        }
        else
        {
            tx = (int)(ry / 2.0) % 32;
            if (ra > 90 && ra < 270)
            {
                tx = 31 - tx;
            }
        }
        for (y = 0; y < lineH; y++)
        {
            int pixel = ((int)ty * 32 + (int)tx) * 3 + (hmt * 32 * 32 * 3);
            int red = All_Textures[pixel + 0] * shade;
            int green = All_Textures[pixel + 1] * shade;
            int blue = All_Textures[pixel + 2] * shade;
            glPointSize(8);
            glColor3ub(red, green, blue);
            glBegin(GL_POINTS);
            glVertex2i(r * 8, y + lineOff);
            glEnd(); // draw vertical wall
            ty += ty_step;
        }

        //---draw floors---
        for (y = lineOff + lineH; y < 640; y++)
        {
            float dy = y - (640 / 2.0), deg = degToRad(ra), raFix = cos(degToRad(FixAng(pa - ra)));
            tx = px / 2 + cos(deg) * 158 * 2 * 32 / dy / raFix;
            ty = py / 2 - sin(deg) * 158 * 2 * 32 / dy / raFix;
            int mp = mapF[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32;
            int pixel = (((int)ty & 31) * 32 + ((int)tx & 31)) * 3 + mp * 3;
            int red = All_Textures[pixel + 0] * 0.7;
            int green = All_Textures[pixel + 1] * 0.7;
            int blue = All_Textures[pixel + 2] * 0.7;
            glPointSize(8);
            glColor3ub(red, green, blue);
            glBegin(GL_POINTS);
            glVertex2i(r * 8, y);
            glEnd();

            //---draw ceiling---
            mp = mapC[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32;
            pixel = (((int)ty & 31) * 32 + ((int)tx & 31)) * 3 + mp * 3;
            red = All_Textures[pixel + 0];
            green = All_Textures[pixel + 1];
            blue = All_Textures[pixel + 2];
            if (mp > 0)
            {
                glPointSize(8);
                glColor3ub(red, green, blue);
                glBegin(GL_POINTS);
                glVertex2i(r * 8, 640 - y);
                glEnd();
            }
        }

        ra = FixAng(ra - 0.5); // go to next ray, 60 total
    }
}