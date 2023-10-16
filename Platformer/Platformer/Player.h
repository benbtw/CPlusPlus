#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player {
private:
	sf::Texture playerTex;
	sf::Sprite player;
	sf::Texture idle_anim[4];
	sf::Texture run_anim[6];
	int anim_counter;
	int index;
	bool collided;
	//bool top, bottom, left, right;
public:
	sf::Vector2f playerPos;
	Player();
	void movement();
	void update(sf::RenderWindow &window);
};