#include "Player.h"

Player::Player() {
	player = LoadTexture("assets/sunnyland/PNG/sprites/player/idle/player-idle-1.png");
	posX = 200;
	posY = 200;
}

void Player::move() {
	if (IsKeyDown(KEY_D))
		posX += 3;
	if (IsKeyDown(KEY_A))
		posX -= 3;
}

void Player::draw() {
	DrawTexture(player, posX, posY, RAYWHITE);
}

void Player::update() {

}