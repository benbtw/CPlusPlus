#include "engineUtil.h"

float dist(float ax, float ay, float bx, float by, float ang)
{
    return (sqrt(bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}

float degToRad(int a)
{
    return a * M_PI / 180.0;
}

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