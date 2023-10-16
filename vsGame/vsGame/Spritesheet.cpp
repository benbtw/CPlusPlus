#include "Spritesheet.h"

Spritesheet::Spritesheet(char const* path, int row, int column)
{
	spritesheet_image = load_bmp(path);

	clip.w = spritesheet_image->w / column;
	clip.h = spritesheet_image->h / row;
}

Spritesheet::~Spritesheet()
{
	SDL_FreeSurface(spritesheet_image);
}

void Spritesheet::select_sprite(int x, int y)
{
	clip.x = x * clip.w;
	clip.y = y * clip.h;
}

void Spritesheet::draw_selected_sprite(SDL_Surface* window_surface, SDL_Rect* position)
{
	SDL_BlitSurface(spritesheet_image, &clip, window_surface, position);
}
