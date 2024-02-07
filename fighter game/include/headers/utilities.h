#ifndef HEADER_FILE
#define HEADER_FILE
#include <SDL.h>
#include <iostream>

class Animations
{
public:
    SDL_Rect idleAnim[8];
    SDL_Rect moveAnim[8];
    SDL_Rect attack1Anim[6];
    SDL_Rect attack2Anim[6];
    SDL_Rect deathAnim[6];
    SDL_Rect jumpAnim[2];
    SDL_Rect dmgAnim[4];

    Animations();
};

#endif