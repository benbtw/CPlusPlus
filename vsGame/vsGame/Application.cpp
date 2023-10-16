#include "Application.h"

Application::Application()
{

	window = SDL_CreateWindow("SDL2 Game",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							680, 480,
							0);

	if (!window) {
		std::cout << "Window error: " << SDL_GetError();
		return;
	}

	win_surface = SDL_GetWindowSurface(window);

	if (!win_surface) {
		std::cout << "Surface error: " << SDL_GetError();
		return;
	}
}

Application::~Application()
{
	SDL_FreeSurface(win_surface);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Application::loop()
{
	bool Running = true;
	while (Running) {
		while (SDL_PollEvent(&win_ev) > 0) {
			player.handle_events(win_ev);
			switch (win_ev.type) {
				case SDL_QUIT:
					Running = false;
					break;
			}
		}

		update(1.0 / 60.0);
		draw();
	}
}

void Application::update(double deltaTime) {
	player.update(deltaTime);
}

void Application::draw()
{
	SDL_FillRect(win_surface, NULL, SDL_MapRGB(win_surface->format, 0, 0, 0));
	player.draw(win_surface);
	SDL_UpdateWindowSurface(window);
}