#pragma once
#include "raylib.h"
#include <iostream>

class Player {
private:
	Texture2D player;
	int posX;
	int posY;
public:
	Player();
	void move();
	void draw();
	void update();
};