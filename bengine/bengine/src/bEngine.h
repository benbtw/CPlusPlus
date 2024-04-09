#pragma once
#ifndef _BENGINE_H
#define _BENGINE_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <vector>

// drawable shapes
typedef struct
{
	int x, y, w, h;
} bRect;

typedef struct
{
	int x, y, w, h;
} bPoint;

typedef struct
{
	int x1, y1, x2, y2;
} bLine;

class bWindow
{
protected:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event e;
	SDL_MouseButtonEvent b;
	SDL_Texture *tex;

	Uint32 frameStart;
	int frameTime;
	int FPS;
	int frameDelay;

	void mousePress(SDL_MouseButtonEvent &b);

	Mix_Chunk *sound;
	Mix_Music *song;

public:

	bWindow();
	~bWindow();

	// window and rendering
	void createWindow(int width, int height, const char *title);
	void createRenderer();
	void startRender();
	void stopRender();
	void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void pollEvents();
	void setFPS(int fps);
	void startClock();

	// Input
	const Uint8 *keys;

	int mouseX;
	int mouseY;

	bool mouseLeft;
	bool mouseRight;
	bool mouseMiddle;
	bool mouseX1;
	bool mouseX2;

	//font, text
	void renderFont(Uint8 r, Uint8 g, Uint8 b, const char *text, int x, int y, int w, int h, const char *fontFile, int fontSize);

	//audio
	void playSound(const char *filename, int v);
	void playMusic(const char *filename, int v);
	void toggleMusic();

	//2d drawing
	void drawRectOutline(const bRect *rect, Uint8 r, Uint8 g, Uint8 b);
	void drawRectFilled(const bRect *rect, Uint8 r, Uint8 g, Uint8 b);
	
	void drawLine(const bLine *line, float width, Uint8 r, Uint8 g, Uint8 b);

	void drawPoint(const bPoint *point, Uint8 r, Uint8 g, Uint8 b);

	void drawImage(const char *filePath, const bRect *Src, const bRect *posSize);

	//3d stuff
};

// key scancodes
enum BKEY_CODE
{
	BKEY_CODE_A = 4,
	BKEY_CODE_B = 5,
	BKEY_CODE_C = 6,
	BKEY_CODE_D = 7,
	BKEY_CODE_E = 8,
	BKEY_CODE_F = 9,
	BKEY_CODE_G = 10,
	BKEY_CODE_H = 11,
	BKEY_CODE_I = 12,
	BKEY_CODE_J = 13,
	BKEY_CODE_K = 14,
	BKEY_CODE_L = 15,
	BKEY_CODE_M = 16,
	BKEY_CODE_N = 17,
	BKEY_CODE_O = 18,
	BKEY_CODE_P = 19,
	BKEY_CODE_Q = 20,
	BKEY_CODE_R = 21,
	BKEY_CODE_S = 22,
	BKEY_CODE_T = 23,
	BKEY_CODE_U = 24,
	BKEY_CODE_V = 25,
	BKEY_CODE_W = 26,
	BKEY_CODE_X = 27,
	BKEY_CODE_Y = 28,
	BKEY_CODE_Z = 29,
	BKEY_CODE_1 = 30,
	BKEY_CODE_2 = 31,
	BKEY_CODE_3 = 32,
	BKEY_CODE_4 = 33,
	BKEY_CODE_5 = 34,
	BKEY_CODE_6 = 35,
	BKEY_CODE_7 = 36,
	BKEY_CODE_8 = 37,
	BKEY_CODE_9 = 38,
	BKEY_CODE_0 = 39,
	BKEY_CODE_RETURN = 40,
	BKEY_CODE_ESCAPE = 41,
	BKEY_CODE_BACKSPACE = 42,
	BKEY_CODE_TAB = 43,
	BKEY_CODE_SPACE = 44,
	BKEY_CODE_MINUS = 45,
	BKEY_CODE_EQUALS = 46,
	BKEY_CODE_LEFTBRACKET = 47,
	BKEY_CODE_RIGHTBRACKET = 48,
	BKEY_CODE_BACKSLASH = 49,
	BKEY_CODE_SEMICOLON = 51,
	BKEY_CODE_APOSTROPHE = 52,
	BKEY_CODE_GRAVE = 53,
	BKEY_CODE_COMMA = 54,
	BKEY_CODE_PERIOD = 55,
	BKEY_CODE_SLASH = 56,
	BKEY_CODE_CAPSLOCK = 57,
	BKEY_CODE_F1 = 58,
	BKEY_CODE_F2 = 59,
	BKEY_CODE_F3 = 60,
	BKEY_CODE_F4 = 61,
	BKEY_CODE_F5 = 62,
	BKEY_CODE_F6 = 63,
	BKEY_CODE_F7 = 64,
	BKEY_CODE_F8 = 65,
	BKEY_CODE_F9 = 66,
	BKEY_CODE_F10 = 67,
	BKEY_CODE_F11 = 68,
	BKEY_CODE_F12 = 69,
	BKEY_CODE_PAUSE = 72,
	BKEY_CODE_INSERT = 73,
	BKEY_CODE_HOME = 74,
	BKEY_CODE_PAGEUP = 75,
	BKEY_CODE_DELETE = 76,
	BKEY_CODE_END = 77,
	BKEY_CODE_PAGEDOWN = 78,
	BKEY_CODE_RIGHT = 79,
	BKEY_CODE_LEFT = 80,
	BKEY_CODE_DOWN = 81,
	BKEY_CODE_UP = 82,
	BKEY_CODE_LCTRL = 224,
	BKEY_CODE_LSHIFT = 225,
	BKEY_CODE_RCTRL = 228,
	BKEY_CODE_RSHIFT = 229
};

#endif