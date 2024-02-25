#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

class Menu
{
private:
    TTF_Font *txt;
    SDL_Color White;

    SDL_Surface *txtMessage;
    SDL_Texture *message;
    SDL_Surface *restartMsg;
    SDL_Texture *rMsg;
    SDL_Surface *exitMsg;
    SDL_Texture *eMsg;
    SDL_Surface *gemMsg;
    SDL_Texture *gMsg;
    SDL_Surface *startMsg;
    SDL_Texture *sMsg;
    SDL_Surface *winMsg;
    SDL_Texture *wMsg;
    SDL_Rect msgRect;
    SDL_Rect restartRect;
    SDL_Rect exitRect;
    SDL_Rect gemRect;

    SDL_Texture *gem;
    SDL_Rect gemSrc;
    SDL_Rect gemPosRect;

    SDL_Texture *menuBG;

    int delay = 0;

public:
    void init(SDL_Renderer *renderer);
    void deathMenu(SDL_Renderer *renderer);
    void mainMenu(SDL_Renderer *renderer);
    void winMenu(SDL_Renderer *renderer);
    void gemCounter(SDL_Renderer *renderer, int &gemCount);
    ~Menu();
    bool start;
};