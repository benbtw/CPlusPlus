#include "GameWindow.h"

bool init() {
    SDL_Window* window = nullptr;
    bool Running = true;
    SDL_Event ev;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "Video Init Error: " << SDL_GetError() << std::endl;

    window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            640, 480, SDL_WINDOW_SHOWN);

    if (window == NULL)
        std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;

    while (Running) {

        while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT)
                Running = false;
        }

        SDL_UpdateWindowSurface(window);

    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}