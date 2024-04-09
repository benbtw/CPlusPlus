#include "bEngine.h"

bWindow::bWindow(){}

bWindow::~bWindow()
{
	Mix_FreeChunk(sound);
	Mix_FreeMusic(song);
	SDL_DestroyTexture(tex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_Quit();
	SDL_Quit();
}

void bWindow::createWindow(int width, int height, const char * title)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! Error: %s\n", SDL_GetError());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! Error: %s\n", SDL_GetError());
	}
}

void bWindow::createRenderer()
{
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! Error: %s\n", SDL_GetError());
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}
}

void bWindow::startRender()
{
	SDL_RenderClear(renderer);
}

void bWindow::stopRender()
{
	SDL_RenderPresent(renderer);
}

void bWindow::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void bWindow::pollEvents()
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			exit(1);
		if (e.type == SDL_MOUSEBUTTONDOWN)
			mousePress(e.button);
		if (e.type == SDL_MOUSEBUTTONUP) {
			mouseLeft = false;
			mouseRight = false;
			mouseMiddle = false;
			mouseX1 = false;
			mouseX2 = false;	
		}
	}

	SDL_GetMouseState(&mouseX, &mouseY);
	keys = SDL_GetKeyboardState(NULL);
}

void bWindow::setFPS(int fps)
{
	FPS = fps;
	frameDelay = 1000 / FPS;
}

void bWindow::startClock()
{
	frameStart = SDL_GetTicks();

	frameTime = SDL_GetTicks() - frameStart;
	if (frameDelay > frameTime)
		SDL_Delay(frameDelay - frameTime);
}

void bWindow::renderFont(Uint8 r, Uint8 g, Uint8 b, const char * text, int x, int y, int w, int h, const char *fontFile, int fontSize)
{
	TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
	SDL_Color color = { r, g, b };
	SDL_Surface *surMsg = TTF_RenderText_Solid(font, text, color);
	SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surMsg);
	SDL_Rect msg_rect = { x, y, w, h };

	SDL_RenderCopy(renderer, message, NULL, &msg_rect);

	SDL_FreeSurface(surMsg);
	SDL_DestroyTexture(message);
	TTF_CloseFont(font);
}

void bWindow::playSound(const char * filename, int v)
{
	sound = Mix_LoadWAV(filename);

	int volume = (MIX_MAX_VOLUME * v) / 100;

	Mix_Volume(-1, volume);
	Mix_PlayChannel(-1, sound, 0);
}

void bWindow::playMusic(const char * filename, int v)
{
	song = Mix_LoadMUS(filename);

	int volume = (MIX_MAX_VOLUME * v) / 100;

	Mix_Volume(-1, volume);
	Mix_PlayMusic(song, -1);
}

void bWindow::toggleMusic()
{
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}

void bWindow::drawRectOutline(const bRect * rect, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Rect rec = { rect->x, rect->y, rect->w, rect->h };
	SDL_SetRenderDrawColor(renderer, r, g, b, 1);
	SDL_RenderDrawRect(renderer, &rec);
}

void bWindow::drawRectFilled(const bRect * rect, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Rect rec = { rect->x, rect->y, rect->w, rect->h };
	SDL_SetRenderDrawColor(renderer, r, g, b, 1);
	SDL_RenderFillRect(renderer, &rec);
}

void bWindow::drawLine(const bLine * line, float width, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_RenderSetScale(renderer, width, 1);
	SDL_SetRenderDrawColor(renderer, r, g, b, 1);
	SDL_RenderDrawLine(renderer, line->x1, line->y1, line->x2, line->y2);
	SDL_RenderSetScale(renderer, 1, 1);
}

void bWindow::drawPoint(const bPoint * point, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 1);
	SDL_Rect rect = {point->x, point->y, point->w, point->h};
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderSetScale(renderer, 1, 1);
}

void bWindow::drawImage(const char * filePath, const bRect * Src, const bRect * posSize)
{
	tex = IMG_LoadTexture(renderer, filePath);
	SDL_Rect src = { Src->x, Src->y, Src->w, Src->h };
	SDL_Rect pos = { posSize->x, posSize->y, posSize->w, posSize->h };
	SDL_RenderCopy(renderer, tex, &src, &pos);
}

void bWindow::mousePress(SDL_MouseButtonEvent & b)
{
	if (b.button == SDL_BUTTON_LEFT)
		mouseLeft = true;
	if (b.button == SDL_BUTTON_MIDDLE)
		mouseMiddle = true;
	if (b.button == SDL_BUTTON_RIGHT)
		mouseRight = true;
	if (b.button == SDL_BUTTON_X1)
		mouseX1 = true;
	if (b.button == SDL_BUTTON_X2)
		mouseX2 = true;
}