#include "headers/TileMap.h"

TileMap::TileMap(SDL_Renderer* renderer) {
	floorSet = IMG_LoadTexture(renderer, "assets/floorSet.png");

	tilePos.x = 0;
	tilePos.y = 0;
	tilePos.w = 64;
	tilePos.h = 64;

	textures = {
		{1, spriteRect(176, 112, 16, 16)},
		{2, spriteRect(192, 112, 16, 16)},
		{3, spriteRect(208, 112, 16, 16)},
		{4, spriteRect(176, 128, 16, 16)},
		{5, spriteRect(192, 128, 16, 16)},
		{6, spriteRect(208, 128, 16, 16)},
		{7, spriteRect(176, 144, 16, 16)},
		{8, spriteRect(192, 144, 16, 16)},
		{9, spriteRect(208, 144, 16, 16)}
	};

	map_one = {
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3},
		{4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6},
		{4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6},
		{4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6},
		{4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6},
		{4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6},
		{4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6},
		{4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6},
		{4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6},
		{4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6},
		{7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9}
	};

	colisionNumbers = {
		2, 4, 6, 8
	};
}

void TileMap::draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < map_one.size(); i++)
	{
		for (int j = 0; j < map_one[i].size(); j++)
		{
			tilePos.x = j * 64;
			tilePos.y = i * 64;
			SDL_RenderCopy(renderer, floorSet, &textures[map_one[i][j]], &tilePos);
			if (std::find(colisionNumbers.begin(), colisionNumbers.end(), map_one[i][j]) != colisionNumbers.end())
				collisionTiles.push_back(tilePos);
		}
	}
}

TileMap::~TileMap()
{
	SDL_DestroyTexture(floorSet);
}