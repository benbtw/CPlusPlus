#include "Player.h"
#include "World.h"

World world;

Player::Player() {
	playerTex.loadFromFile("GAMEART/sunnyland/PNG/sprites/player/idle/player-idle-1.png");
	player.setTexture(playerTex);
	idle_anim[0].loadFromFile("GAMEART/sunnyland/PNG/sprites/player/idle/player-idle-1.png");
	idle_anim[1].loadFromFile("GAMEART/sunnyland/PNG/sprites/player/idle/player-idle-2.png");
	idle_anim[2].loadFromFile("GAMEART/sunnyland/PNG/sprites/player/idle/player-idle-3.png");
	idle_anim[3].loadFromFile("GAMEART/sunnyland/PNG/sprites/player/idle/player-idle-4.png");
	run_anim[0].loadFromFile("GAMEART/sunnyland/PNG/sprites/player/Run/player-run-1.png");
	run_anim[1].loadFromFile("GAMEART/sunnyland/PNG/sprites/player/Run/player-run-2.png");
	run_anim[2].loadFromFile("GAMEART/sunnyland/PNG/sprites/player/Run/player-run-3.png");
	run_anim[3].loadFromFile("GAMEART/sunnyland/PNG/sprites/player/Run/player-run-4.png");
	run_anim[4].loadFromFile("GAMEART/sunnyland/PNG/sprites/player/Run/player-run-5.png");
	run_anim[5].loadFromFile("GAMEART/sunnyland/PNG/sprites/player/Run/player-run-6.png");
	anim_counter = 0;
	index = 0;
	player.setOrigin(sf::Vector2f(player.getTexture()->getSize().x * 0.5, player.getTexture()->getSize().y * 0.5));
	player.setPosition(100, 310);
	playerPos = player.getPosition();
	player.setScale(1.5, 1.5);
}

void Player::movement() {
	anim_counter++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (anim_counter > 6) {
			index += 1;
			anim_counter = 0;
		}
		if (index == 4)
			index = 0;
		player.setScale(1.5f, 1.5f);
		player.setTexture(run_anim[index]);
		player.move(5, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (anim_counter > 6) {
			index += 1;
			anim_counter = 0;
		}
		if (index == 4)
			index = 0;
		player.setScale(-1.5f, 1.5f);
		player.setTexture(run_anim[index]);
		player.move(-5, 0);
	} else {
		if (anim_counter > 6) {
			index += 1;
			anim_counter = 0;
		}
		if (index == 4)
			index = 0;
		player.setTexture(idle_anim[index]);
	}
	playerPos = player.getPosition();
}

void Player::update(sf::RenderWindow& window) {
	window.draw(player);
	movement();
}