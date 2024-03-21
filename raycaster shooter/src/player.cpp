#include "player.h"

Player::Player()
{
    player.x = px;
    player.y = py;
    player.w = 15;
    player.h = 15;
    pdx = cos(degToRad(pa));
    pdy = -sin(degToRad(pa));
}

void Player::movement(int map[], int mapX)
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    int xo = 0;
    if (pdx < 0)
    {
        xo = -20;
    }
    else
    {
        xo = 20;
    }
    int yo = 0;
    if (pdy < 0)
    {
        yo = -20;
    }
    else
    {
        yo = 20;
    }
    int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0, ipx_sub_xo = (px - xo) / 64.0;
    int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0, ipy_sub_yo = (py - yo) / 64.0;

    if (keyState[SDL_SCANCODE_W])
    {
        if (map[ipy * mapX + ipx_add_xo] == 0)
        {
            px += pdx * 1.5;
        }
        if (map[ipy_add_yo * mapX + ipx] == 0)
        {
            py += pdy * 1.5;
        }
    }
    if (keyState[SDL_SCANCODE_S])
    {
        if (map[ipy * mapX + ipx_sub_xo] == 0)
        {
            px -= pdx * 1.5;
        }
        if (map[ipy_sub_yo * mapX + ipx] == 0)
        {
            py -= pdy * 1.5;
        }
    }
    if (keyState[SDL_SCANCODE_A])
    {
        pa += 2.1;
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

    player.x = px;
    player.y = py;
}