#pragma once
#include <SDL.h>

class Player {
private:
	SDL_Surface* player;
public:
	void movement();
	void update();
};