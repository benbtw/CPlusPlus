#include "world.h"
#include "textures.h"

World::~World()
{
    SDL_DestroyTexture(mapTexture);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(middle);
}

void World::loadMapFile()
{

    n = 28;
    m = 90;

    std::vector<std::vector<int>> vec(n, std::vector<int>(m));

    std::ifstream iFile;
    iFile.open("res/map.txt");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            iFile >> vec[i][j];

    iFile.close();

    map = vec;
}

void World::init(SDL_Renderer *renderer)
{
    mapTexture = IMG_LoadTexture(renderer, "res/TileSheet.png");
    background = IMG_LoadTexture(renderer, "res/back.png");
    middle = IMG_LoadTexture(renderer, "res/middle.png");
    middlePos = {0, 150, 200, 400};

    needsBackgroundNumbers = {
        920, 787, 868, 927, 928, 918, 880, 703, 729, 678, 679, 705, 731, 872, 924, 677};

    colisionNumbers = {
        28, 34, 87, 139, 84, 80, 121, 30, 127, 49, 50, 380, 382, 384, 125, 32, 28, 272, 119, 40, 41, 927, 928, 846, 847, 872, 873, 924,
        524, 525, 550, 551, 200, 522, 886, 887, 912, 913, 198, 134, 348, 302, 306, 346, 350, 254, 132, 289, 136, 66};

    spikes = {};

    tilePos.w = 48;
    tilePos.h = 48;
    tilePos.x = 0;
    tilePos.y = 0;
    colPos.w = 48;
    colPos.h = 48;
    colPos.x = 0;
    colPos.y = 0;

    n = 28;
    m = 12;
}

void World::draw(SDL_Renderer *renderer, int camX, int camY)
{
    colTiles.clear();
    spikes.clear();

    SDL_RenderCopy(renderer, background, NULL, NULL);
    for (int i = 0; i < 6; i++)
    {
        middlePos = {i * 200, 150, 200, 400};
        SDL_RenderCopy(renderer, middle, NULL, &middlePos);
    }

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            tilePos.x = j * 48 - camX;
            tilePos.y = i * 48 - 200 - camY;
            colPos.x = j * 48;
            colPos.y = i * 48 - 200;
            if (std::find(needsBackgroundNumbers.begin(), needsBackgroundNumbers.end(), map[i][j]) != needsBackgroundNumbers.end())
                SDL_RenderCopy(renderer, mapTexture, &mapTextures[471], &tilePos);
            if (std::find(colisionNumbers.begin(), colisionNumbers.end(), map[i][j]) != colisionNumbers.end())
                colTiles.push_back(colPos);
            if (map[i][j] == 868 || map[i][j] == 920 || map[i][j] == 918)
                spikes.push_back(colPos);
            SDL_RenderCopy(renderer, mapTexture, &mapTextures[map[i][j]], &tilePos);
        }
    }
}

void World::update(SDL_Rect &playerBox, bool &death)
{
    for (int i = 0; i < spikes.size(); i++)
        if (SDL_HasIntersection(&playerBox, &spikes[i]))
            death = true;
}