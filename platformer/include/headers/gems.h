#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

class Gem
{
private:
    SDL_Texture *gem;
    SDL_Rect gemRect;
    std::vector<SDL_Rect> gems;
    std::vector<SDL_Rect> positions;

    int delay, index;

public:
    void update(SDL_Rect playerBox);
    void draw(SDL_Renderer *renderer, SDL_Rect cameraRect);
    ~Gem();
    void init(SDL_Renderer *renderer);
    int gemCount;
};