#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

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
    void update(SDL_Rect &playerBox, bool &death);
    void draw(SDL_Renderer *renderer, int camX, int camY);
    ~World();
    std::vector<SDL_Rect> colTiles;
    std::vector<SDL_Rect> spikes;
};