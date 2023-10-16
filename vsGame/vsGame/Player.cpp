#include "Player.h"

Player::Player(): spritesheet("player-idle.bmp",1,4)
{

	player_pos.x = 0;
	player_pos.y = 0;
	player_pos.w = 32;
	player_pos.h = 32;

	p_x = 0.0;
	p_y = 0.0;

	spritesheet.select_sprite(0, 0);
}

Player::~Player()
{
}

void Player::update(double deltaTime)
{
	switch (direction) {
		case Direction::NONE:
			p_x += 0.0;
			p_y += 0.0;
			break;
		case Direction::UP:
			p_y = p_y - (5.0 * deltaTime);
			break;
		case Direction::DOWN:
			p_y = p_y + (5.0 * deltaTime);
			break;
		case Direction::LEFT:
			p_x = p_x - (5.0 * deltaTime);
			break;
		case Direction::RIGHT:
			p_x = p_x + (5.0 * deltaTime);
			break;
	}

	player_pos.x = p_x;
	player_pos.y = p_y;
}

void Player::draw(SDL_Surface* window_surface)
{
	spritesheet.draw_selected_sprite(window_surface, &player_pos);
}

void Player::handle_events(SDL_Event const& event)
{
	switch (event.type) {

		/*case SDL_KEYUP:
			direction = Direction::NONE;
			break;*/

		case SDL_KEYDOWN:
			Uint8 const* keys = SDL_GetKeyboardState(nullptr);

			if (keys[SDL_SCANCODE_W] == 1)
				direction = Direction::UP;
			else if (keys[SDL_SCANCODE_S] == 1)
				direction = Direction::DOWN;
			else if (keys[SDL_SCANCODE_A] == 1)
				direction = Direction::LEFT;
			else if (keys[SDL_SCANCODE_D] == 1)
				direction = Direction::RIGHT;
			break;
	}
}
