#pragma once
#include <iostream>
#include "SDL.h"
#include "Spritesheet.h"

class Player
{

public:

	enum class Direction {
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Player();
	~Player();

	void update(double deltaTime);
	void draw(SDL_Surface* window_surface);
	void handle_events(SDL_Event const& event);

private:
	Spritesheet spritesheet;
	SDL_Rect player_pos;
	double p_x;
	double p_y;

	Direction direction;
};

