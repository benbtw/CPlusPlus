#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

/*
    create the world, load in from text file do the same in this design as the top down
*/

class World
{
private:
    SDL_Texture *mapTexture;
    SDL_Texture *background;
    SDL_Texture *middle;
    int n;
    int m;
    std::vector<std::vector<int>> map;
    std::vector<int> colisionNumbers;
    std::vector<int> needsBackgroundNumbers;
    SDL_Rect tilePos;
    SDL_Rect middlePos;
    SDL_Rect colPos;

public:
    void loadMapFile();
    void init(SDL_Renderer *renderer);
    void draw(SDL_Renderer *renderer, int camX, int camY);
    ~World();
    std::vector<SDL_Rect> colTiles;
};