#include "player.h"

Player::Player()
{
    player.x = px;
    player.y = py;
    player.w = 15;
    player.h = 15;
    pdx = cos(pa) * 5;
    pdy = sin(pa) * 5;
}

void Player::movement()
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_W])
    {
        py += pdy * 1.5;
        px += pdx * 1.5;
    }
    if (keyState[SDL_SCANCODE_A])
    {
        pa += 1.5;
        pa = FixAng(pa);
        pdx = cos(degToRad(pa));
        pdy = -sin(degToRad(pa));
    }
    if (keyState[SDL_SCANCODE_D])
    {
        pa -= 1.5;
        pa = FixAng(pa);
        pdx = cos(degToRad(pa));
        pdy = -sin(degToRad(pa));
    }
    if (keyState[SDL_SCANCODE_S])
    {
        py -= pdy * 1.5;
        px -= pdx * 1.5;
    }

    player.x = px;
    player.y = py;
}