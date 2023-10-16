#pragma once
#include "utilities.h"
#include "SDL.h"

class Spritesheet
{
public:
	Spritesheet(char const* path, int row, int column);
	~Spritesheet();

	void select_sprite(int x, int y);
	void draw_selected_sprite(SDL_Surface* window_surface, SDL_Rect* position);

private:
	SDL_Rect clip;
	SDL_Surface* spritesheet_image;
};

