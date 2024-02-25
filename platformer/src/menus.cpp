#include "menus.h"

void Menu::init(SDL_Renderer *renderer)
{
    if (TTF_Init() < 0)
        printf("SDL_TTF Init error, SDL_Error: ", SDL_GetError());

    txt = TTF_OpenFont("res/monogram.ttf", 50);
    White = {255, 255, 255};

    txtMessage = TTF_RenderText_Solid(txt, "Game Over", White);
    message = SDL_CreateTextureFromSurface(renderer, txtMessage);
    msgRect = {1024 / 2 - 250, 75, 500, 100};

    restartMsg = TTF_RenderText_Solid(txt, "Restart? (r)", White);
    rMsg = SDL_CreateTextureFromSurface(renderer, restartMsg);
    restartRect = {1024 / 2 - 150, 275, 250, 50};

    exitMsg = TTF_RenderText_Solid(txt, "Exit? (e)", White);
    eMsg = SDL_CreateTextureFromSurface(renderer, exitMsg);
    exitRect = {1024 / 2 - 150, 375, 250, 50};

    restartMsg = TTF_RenderText_Solid(txt, "Restart (r)", White);
    rMsg = SDL_CreateTextureFromSurface(renderer, restartMsg);
    restartRect = {1024 / 2 - 150, 275, 250, 50};

    exitMsg = TTF_RenderText_Solid(txt, "Exit (e)", White);
    eMsg = SDL_CreateTextureFromSurface(renderer, exitMsg);
    exitRect = {1024 / 2 - 150, 375, 250, 50};

    startMsg = TTF_RenderText_Solid(txt, "Play (p)", White);
    sMsg = SDL_CreateTextureFromSurface(renderer, startMsg);

    winMsg = TTF_RenderText_Solid(txt, "You Win!", White);
    wMsg = SDL_CreateTextureFromSurface(renderer, winMsg);

    gemRect = {1024 - 200, 20, 150, 50};

    gem = IMG_LoadTexture(renderer, "res/gem.png");
    gemSrc = {0, 0, 15, 13};
    gemPosRect = {1024 - 250, 32, 42, 40};

    menuBG = IMG_LoadTexture(renderer, "res/mainMenuimg.png");
    SDL_SetTextureAlphaMod(menuBG, 155);

    start = true;

    delay = 0;
}

void Menu::deathMenu(SDL_Renderer *renderer)
{
    restartRect = {1024 / 2 - 150, 275, 250, 50};
    exitRect = {1024 / 2 - 150, 375, 250, 50};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, message, NULL, &msgRect);
    SDL_RenderCopy(renderer, rMsg, NULL, &restartRect);
    SDL_RenderCopy(renderer, eMsg, NULL, &exitRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderPresent(renderer);
}

void Menu::gemCounter(SDL_Renderer *renderer, int &gemCount)
{
    std::string count = std::to_string(gemCount) + " / 14";
    gemMsg = TTF_RenderText_Solid(txt, count.c_str(), White);
    gMsg = SDL_CreateTextureFromSurface(renderer, gemMsg);

    SDL_RenderCopy(renderer, gMsg, NULL, &gemRect);
    SDL_RenderCopy(renderer, gem, &gemSrc, &gemPosRect);
}

void Menu::mainMenu(SDL_Renderer *renderer)
{
    restartRect = {1024 / 2 - 150, 175, 250, 50};
    exitRect = {1024 / 2 - 150, 275, 250, 50};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menuBG, NULL, NULL);
    SDL_RenderCopy(renderer, sMsg, NULL, &restartRect);
    SDL_RenderCopy(renderer, eMsg, NULL, &exitRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderPresent(renderer);
    delay = 0;
}

void Menu::winMenu(SDL_Renderer *renderer)
{
    restartRect = {1024 / 2 - 150, 200, 250, 50};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, wMsg, NULL, &restartRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderPresent(renderer);
    delay++;
    if (delay >= 90)
    {
        start = true;
        mainMenu(renderer);
    }
}

Menu::~Menu()
{
    SDL_DestroyTexture(message);
    SDL_FreeSurface(txtMessage);
    SDL_DestroyTexture(rMsg);
    SDL_FreeSurface(restartMsg);
    SDL_DestroyTexture(eMsg);
    SDL_FreeSurface(exitMsg);
    SDL_DestroyTexture(gMsg);
    SDL_FreeSurface(gemMsg);
    SDL_DestroyTexture(sMsg);
    SDL_FreeSurface(startMsg);
    SDL_DestroyTexture(wMsg);
    SDL_FreeSurface(winMsg);
    free(txt);
    txt = NULL;
}