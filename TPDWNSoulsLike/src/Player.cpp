#include "headers/Player.h"
#include <iostream>

Player::~Player()
{
	SDL_DestroyTexture(player);
}

Player::Player(SDL_Renderer* renderer)
{
	player = IMG_LoadTexture(renderer, "assets/playerSheet.png");
	animDelay = 0;
	index = 0;
	up = false;
	down = true;
	left = false;
	right = false;
	direction = 'S';

	// animations
	playerDownAnim[0] = spriteRect(0, 0, 16, 16);
	playerDownAnim[1] = spriteRect(0, 16, 16, 16);
	playerDownAnim[2] = spriteRect(0, 32, 16, 16);
	playerDownAnim[3] = spriteRect(0, 48, 16, 16);

	playerUpAnim[0] = spriteRect(16, 0, 16, 16);
	playerUpAnim[1] = spriteRect(16, 16, 16, 16);
	playerUpAnim[2] = spriteRect(16, 32, 16, 16);
	playerUpAnim[3] = spriteRect(16, 48, 16, 16);

	playerLeftAnim[0] = spriteRect(32, 0, 16, 16);
	playerLeftAnim[1] = spriteRect(32, 16, 16, 16);
	playerLeftAnim[2] = spriteRect(32, 32, 16, 16);
	playerLeftAnim[3] = spriteRect(32, 48, 16, 16);

	playerRightAnim[0] = spriteRect(48, 0, 16, 16);
	playerRightAnim[1] = spriteRect(48, 16, 16, 16);
	playerRightAnim[2] = spriteRect(48, 32, 16, 16);
	playerRightAnim[3] = spriteRect(48, 48, 16, 16);

	// player sprite sheet selection
	playerSrc = spriteRect(0, 0, 16, 16);

	// player size setup
	playerPos = spriteRect(100, 500, 64, 64);

	speed = 2;
}

bool Player::isTouchingLeft(SDL_Rect rect)
{
	return playerPos.x + 34 + velocity.x > rect.x &&
		playerPos.x < rect.x &&
		playerPos.y + 34 > rect.y &&
		playerPos.y < rect.y + 34;
}

bool Player::isTouchingRight(SDL_Rect rect)
{
	return playerPos.x + velocity.x < rect.x + 34 &&
				playerPos.x + 34 > rect.x + 34 &&
				playerPos.y + 34 > rect.y &&
				playerPos.y < rect.y + 34;
}

bool Player::isTouchingTop(SDL_Rect rect)
{
	return playerPos.y + 34 + velocity.y > rect.y &&
				playerPos.y < rect.y &&
				playerPos.x + 34 > rect.x &&
				playerPos.x < rect.x + 34;
}

bool Player::isTouchingBottom(SDL_Rect rect)
{
	return playerPos.y + velocity.y < rect.y + 34 &&
				playerPos.y + 34 > rect.y + 34 &&
				playerPos.x+ 34 > rect.x &&
				playerPos.x < rect.x + 34;
}

void Player::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, player, &playerSrc, &playerPos);
}

void Player::movement(SDL_Event &e, std::vector<SDL_Rect> tiles)
{
	animDelay++;
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_W])
	{
		up = true;
		direction = 'W';
		playerSrc = playerUpAnim[index];
		velocity.y -= speed;
	}
	else up = false;
	if (keyState[SDL_SCANCODE_A])
	{
		left = true;
		direction = 'A';
		playerSrc = playerLeftAnim[index];
		velocity.x -= speed;
	}
	else left = false;
	if (keyState[SDL_SCANCODE_D])
	{
		right = true;
		direction = 'D';
		playerSrc = playerRightAnim[index];
		velocity.x += speed;
	}
	else right = false;
	if (keyState[SDL_SCANCODE_S])
	{
		down = true;
		direction = 'S';
		//playerPos.y += speed;
		playerSrc = playerDownAnim[index];
		velocity.y += speed;
	}
	else down = false;

	if (!up && !down && !left && !right)
	{
		switch (direction)
		{
		case 'S':
			playerSrc = playerDownAnim[0];
			break;
		case 'W':
			playerSrc = playerUpAnim[0];
			break;
		case 'A':
			playerSrc = playerLeftAnim[0];
			break;
		case 'D':
			playerSrc = playerRightAnim[0];
			break;
		}
	}

	if (animDelay == 25)
	{
		animDelay = 0;
		index++;
		if (index > 3)
			index = 0;
	}

	for (SDL_Rect tile : tiles)
	{
		if (velocity.x > 0 && isTouchingLeft(tile))
		{
			playerPos.x = tile.x - 34;
			velocity.x = 0;
		}
		if (velocity.x < 0 && isTouchingRight(tile))
		{
			playerPos.x = tile.x + 34;
			velocity.x = 0;
		}

		if (velocity.y > 0 && isTouchingTop(tile))
		{
			playerPos.y = tile.y - 34;
			velocity.y = 0;
		}
		if (velocity.y < 0 && isTouchingBottom(tile))
		{
			playerPos.y = tile.y + 34;
			velocity.y = 0;
		}
	}

	playerPos.x += velocity.x;
	playerPos.y += velocity.y;
	velocity.x = 0;
	velocity.y = 0;
}