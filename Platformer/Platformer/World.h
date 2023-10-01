#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class World {
private:
	sf::Texture grassTex;
	sf::Texture dirtTex;
	sf::Texture backTex;
	sf::Sprite background;
	sf::Sprite grass;
	sf::Sprite dirt;
public:
	sf::Vector2f grassPos = grass.getPosition();
	sf::Vector2f dirtPos = dirt.getPosition();
	static int mapArray[6][20];
	World();
	void draw(sf::RenderWindow& window);
};