#include "World.h"
#include "Player.h"

#define tileset  "GAMEART/sunnyland/png/environment/layers/tileset.png"

Player player;

World::World() {
	grassTex.loadFromFile(tileset, sf::IntRect(42,10,32,32));
	dirtTex.loadFromFile(tileset, sf::IntRect(106, 10, 32, 32));
	backTex.loadFromFile("GAMEART/sunnyland/png/environment/layers/back.png");
	background.setTexture(backTex);
	background.setScale(2, 2);
	grass.setScale(2, 2);
	dirt.setScale(2, 2);
	grass.setTexture(grassTex);
	dirt.setTexture(dirtTex);
}

int World::mapArray[6][20] = {
	{0,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5,5,0},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

void World::draw(sf::RenderWindow& window) {
	window.draw(background);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 6; j++) {
			if (mapArray[j][i] == 0) {
				grass.setPosition((i * 32) - 12, (j * 32) + 288);
				grassPos = grass.getPosition();
				window.draw(grass);
			}
			else if (mapArray[j][i] == 1) {
				dirt.setPosition((i * 32) - 12, (j * 32) + 288);
				dirtPos = dirt.getPosition();
				window.draw(dirt);
			}
		}
	}
}