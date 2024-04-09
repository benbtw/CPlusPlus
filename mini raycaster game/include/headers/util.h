#pragma once
#include <math.h>
#include <cmath>
#define PI 3.14159265359
#define P2 PI / 2
#define P3 3 * PI / 2
#define DR 0.0174533 // one degree in radians

inline float frame1, frame2, fps;

inline float dist(float ax, float ay, float bx, float by, float ang)
{
    return (sqrt(bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}

inline float degToRad(float a)
{
    return a * M_PI / 180.0;
}

inline float FixAng(float a)
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

//-----------------------------MAP----------------------------------------------
#define mapX 8  // map width
#define mapY 8  // map height
#define mapS 64 // map cube size

inline int mapW[] = // walls
    {
        1, 1, 1, 1, 1, 1, 1, 1,
        5, 0, 0, 1, 0, 0, 0, 1,
        1, 0, 0, 3, 0, 1, 0, 1,
        1, 1, 3, 1, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1};

inline int mapF[] = // floors
    {
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2};

inline int mapC[] = // ceiling
    {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1};

inline int depth[120]; // depth for sprites