#pragma once
#include <iostream>
#include "SDL.h"
#include "Player.h"

class Application
{
private:
	SDL_Window* window;
	SDL_Surface* win_surface;
	SDL_Event win_ev;

	Player player;

public:

	Application();
	~Application();

	void loop();
	void update(double deltaTime);
	void draw();

};

