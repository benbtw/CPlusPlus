#pragma once
#include <math.h>
#define PI 3.14159265359
#define P2 PI / 2
#define P3 3 * PI / 2
#define DR 0.0174533 // one degree in radians

float dist(float ax, float ay, float bx, float by, float ang);
float degToRad(int a);
int FixAng(int a);