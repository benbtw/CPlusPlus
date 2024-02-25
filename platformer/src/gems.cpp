#include "gems.h"

void Gem::init(SDL_Renderer *renderer)
{
    gem = IMG_LoadTexture(renderer, "res/gem.png");

    gemRect = {0, 0, 15, 13};

    gems = {
        {438, 244, 32, 30},
        {1012, 244, 32, 30},
        {620, 916, 32, 30},
        {1810, 772, 32, 30},
        {1944, 724, 32, 30},
        {2119, 772, 32, 30},
        {2322, 724, 32, 30},
        {2622, 820, 32, 30},
        {3026, 916, 32, 30},
        {2589, 196, 32, 30},
        {2736, 196, 32, 30},
        {2883, 196, 32, 30},
        {3870, 244, 32, 30},
        {4178, 244, 32, 30}};

    positions = {
        {438, 244, 32, 30},
        {1012, 244, 32, 30},
        {620, 916, 32, 30},
        {1810, 772, 32, 30},
        {1944, 724, 32, 30},
        {2119, 772, 32, 30},
        {2322, 724, 32, 30},
        {2622, 820, 32, 30},
        {3026, 916, 32, 30},
        {2589, 196, 32, 30},
        {2736, 196, 32, 30},
        {2883, 196, 32, 30},
        {3870, 244, 32, 30},
        {4178, 244, 32, 30}};

    gemCount = 0;

    index = 0;
}

void Gem::update(SDL_Rect playerBox)
{

    delay++;

    if (delay == 15)
    {
        index++;
        delay = 0;
        if (index >= 5)
            index = 0;
    }

    for (int i = 0; i < positions.size(); i++)
    {
        if (SDL_HasIntersection(&playerBox, &positions[i]))
        {
            gemCount++;
            positions.erase(positions.begin() + i);
        }
    }
}

void Gem::draw(SDL_Renderer *renderer, SDL_Rect cameraRect)
{
    for (int i = 0; i < positions.size(); i++)
    {
        SDL_Rect drawingRect = {positions[i].x - cameraRect.x, positions[i].y - cameraRect.y, 32, 30};
        SDL_RenderCopy(renderer, gem, &gemRect, &drawingRect);
    }
}

Gem::~Gem()
{
    SDL_DestroyTexture(gem);
}