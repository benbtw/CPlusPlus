#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Sprites.h"

class Player
{
private:
	SDL_Texture* player;
	SDL_Rect playerSrc; // spritesheet origin
	SDL_Rect playerPos;
	SDL_Rect playerUpAnim[4];
	SDL_Rect playerRightAnim[4];
	SDL_Rect playerLeftAnim[4];
	SDL_Rect playerDownAnim[4];
	int speed;
	int animDelay;
	int index;
	char direction;
	bool up, down, left, right;
public:
	void draw(SDL_Renderer* renderer);
	void movement(SDL_Event &e);
	Player(SDL_Renderer* renderer);

	~Player();
};

