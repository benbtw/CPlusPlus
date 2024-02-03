#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Sprites.h"
#include <vector>
#include <map>
#include <algorithm>

class TileMap
{
private:
	SDL_Texture* floorSet;
	std::map<int, SDL_Rect> textures;
	std::vector <std::vector<int>> map_one;
	std::vector<int> colisionNumbers;
	SDL_Rect tilePos;
public:
	TileMap(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);
	std::vector<SDL_Rect> collisionTiles;
	~TileMap();
};