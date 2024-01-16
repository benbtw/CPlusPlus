#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Player.h"

const int SC_WIDTH = 1280;
const int SC_HEIGHT = 720;

int main(int argc, char* argvs[])
{

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL Init error, SDL_Error: " << SDL_GetError() << std::endl;

	window = SDL_CreateWindow("2D Souls Like", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		SC_WIDTH, SC_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr)
		std::cout << "SDL Window error, SDL_Error: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr)
		std::cout << "SDL Renderer error, SDL_Error: " << SDL_GetError() << std::endl;

	SDL_Surface* icon = IMG_Load("assets/icon.png");
	SDL_SetWindowIcon(window, icon);

	Player p = Player(renderer);

	SDL_Event e;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				running = false;
		}

		p.movement(e);

		SDL_RenderClear(renderer);

		p.draw(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(icon);
	SDL_Quit();
	return 0;
}