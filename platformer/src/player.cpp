#include "player.h"

void Player::init(SDL_Renderer *renderer)
{
    pTex = IMG_LoadTexture(renderer, "res/PlayerSheet.png");
    pSrc = {0, 0, 32, 32};
    pPos = {100, 232, 80, 80};
    playerBox.x = pPos.x - 19;
    playerBox.y = pPos.y - 27;
    playerBox.w = 40;
    playerBox.h = 56;

    idleLeftAnim[0] = {0, 0, 32, 32};
    idleLeftAnim[1] = {33, 0, 32, 32};
    idleLeftAnim[2] = {66, 0, 32, 32};
    idleLeftAnim[3] = {99, 0, 32, 32};

    idleRightAnim[0] = {0, 225, 32, 32};
    idleRightAnim[1] = {33, 225, 32, 32};
    idleRightAnim[2] = {66, 225, 32, 32};
    idleRightAnim[3] = {99, 225, 32, 32};

    rightAnim[0] = {0, 33, 32, 32};
    rightAnim[1] = {33, 33, 32, 32};
    rightAnim[2] = {66, 33, 32, 32};
    rightAnim[3] = {99, 33, 32, 32};
    rightAnim[4] = {132, 33, 32, 32};
    rightAnim[5] = {165, 33, 32, 32};

    climbAnim[0] = {0, 66, 32, 32};
    climbAnim[1] = {33, 66, 32, 32};
    climbAnim[2] = {66, 66, 32, 32};

    jumpRightAnim[0] = {0, 160, 32, 32};
    jumpRightAnim[1] = {33, 160, 32, 32};

    jumpLeftAnim[0] = {32, 256, 32, 32};
    jumpLeftAnim[1] = {0, 256, 32, 32};

    leftAnim[0] = {0, 193, 32, 32};
    leftAnim[1] = {33, 193, 32, 32};
    leftAnim[2] = {66, 193, 32, 32};
    leftAnim[3] = {99, 193, 32, 32};
    leftAnim[4] = {132, 193, 32, 32};
    leftAnim[5] = {165, 193, 32, 32};

    delay = 0;
    index = 0;
    maxIndex = 2;
    velocity.x = 0;
    velocity.y = 0;
    gravity.x = 0;
    gravity.y = -6;
    speed = 50;
    direction = 'r';
    jumpSpeed = 140;
    sum = 0;
    death = false;
}

bool Player::isTouchingLeft(SDL_Rect &rect)
{
    return playerBox.x + 40 + velocity.x > rect.x &&
           playerBox.x < rect.x &&
           playerBox.y + 56 > rect.y &&
           playerBox.y < rect.y + rect.h;
}

bool Player::isTouchingRight(SDL_Rect &rect)
{
    return playerBox.x + velocity.x < rect.x + rect.w &&
           playerBox.x + 40 > rect.x + rect.w &&
           playerBox.y + 56 > rect.y &&
           playerBox.y < rect.y + rect.h;
}

bool Player::isTouchingTop(SDL_Rect &rect)
{
    return playerBox.y + 56 + velocity.y > rect.y &&
           playerBox.y < rect.y &&
           playerBox.x + 40 > rect.x &&
           playerBox.x < rect.x + rect.h;
}

bool Player::isTouchingBottom(SDL_Rect &rect)
{
    return playerBox.y + velocity.y < rect.y + rect.h &&
           playerBox.y + 56 > rect.y + rect.h &&
           playerBox.x + 40 > rect.x &&
           playerBox.x < rect.x + rect.h;
}

void Player::movement(std::vector<SDL_Rect> &tiles, SDL_Rect cameraRect, float dt)
{

    delay++;
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    speed = 50;
    gravity.y = -15;

    if (!grounded && !(playerBox.x >= 1520 && playerBox.x <= 1550 && playerBox.y >= 322 && playerBox.y <= 898))
        velocity.y -= gravity.y;

    if (keyState[SDL_SCANCODE_W] && !top && (playerBox.x >= 1520 && playerBox.x <= 1550 && playerBox.y >= 322 && playerBox.y <= 900))
    {
        gravity.y = 0;
        velocity.y -= speed * dt;
        maxIndex = 3;
        pSrc = climbAnim[index];
    }
    if (keyState[SDL_SCANCODE_A] && playerBox.x >= -16 && !left)
    {
        velocity.x -= speed * dt;
        direction = 'l';
        maxIndex = 6;
        pSrc = leftAnim[index];
    }
    if (keyState[SDL_SCANCODE_D] && playerBox.x <= 4260 && !right)
    {
        velocity.x += speed * dt;
        direction = 'r';
        maxIndex = 6;
        pSrc = rightAnim[index];
    }
    if (keyState[SDL_SCANCODE_S] && !bottom && (playerBox.x >= 1520 && playerBox.x <= 1550 && playerBox.y >= 322 && playerBox.y <= 900))
    {
        gravity.y = 0;
        velocity.y += speed * dt;
        maxIndex = 3;
        pSrc = climbAnim[index];
    }
    if ((keyState[SDL_SCANCODE_SPACE] && keyState[SDL_SCANCODE_A]) ||
        (keyState[SDL_SCANCODE_SPACE] && keyState[SDL_SCANCODE_D]) || (keyState[SDL_SCANCODE_SPACE]) && grounded && !top)
    {
        if (direction == 'l')
            pSrc = jumpLeftAnim[0];
        else if (direction == 'r')
            pSrc = jumpRightAnim[0];
        velocity.y -= 8;
        gravity.y = -15;
        playerBox.y += velocity.y * dt;
        velocity.y += gravity.y * dt;
        sum += 10;
        if (sum >= 160)
        {
            grounded = false;
            if (direction == 'l')
                pSrc = jumpLeftAnim[1];
            else if (direction == 'r')
                pSrc = jumpRightAnim[1];
        }
    }
    else
        grounded = false;

    if (!keyState[SDL_SCANCODE_S] && !keyState[SDL_SCANCODE_W] &&
        !keyState[SDL_SCANCODE_A] && !keyState[SDL_SCANCODE_D] && !keyState[SDL_SCANCODE_SPACE])
    {
        maxIndex = 4;
        if (direction == 'r')
            pSrc = idleLeftAnim[index];
        else
            pSrc = idleRightAnim[index];
    }

    if (delay == 15)
    {
        delay = 0;
        index++;
        if (index >= maxIndex)
            index = 0;
    }

    for (SDL_Rect tile : tiles)
    {
        if (velocity.x > 0 && isTouchingLeft(tile))
        {
            playerBox.x = tile.x - tile.w + 2;
            velocity.x = 0;
            right = true;
        }
        if (velocity.x < 0 && isTouchingRight(tile))
        {
            playerBox.x = tile.x + tile.w;
            velocity.x = 0;
            left = true;
        }
        if (velocity.y > 0 && isTouchingTop(tile) && !(playerBox.x >= 1520 && playerBox.x <= 1550 && playerBox.y >= 322 && playerBox.y <= 700))
        {
            playerBox.y = tile.y - tile.h - 8;
            velocity.y = 0;
            bottom = true;
            grounded = true;
            sum = 0;
        }
        if (velocity.y < 0 && isTouchingBottom(tile) && !(playerBox.x >= 1520 && playerBox.x <= 1550 && playerBox.y >= 322 && playerBox.y <= 700))
        {
            playerBox.y = tile.y + tile.h;
            velocity.y = 0;
            top = true;
        }
    }

    playerBox.x += velocity.x;
    playerBox.y += velocity.y;
    pPos.x = playerBox.x - 19;
    pPos.y = playerBox.y - 27;
    velocity.x = 0;
    velocity.y = 0;

    if (playerBox.y >= 950)
        death = true;

    left = false;
    bottom = false;
    right = false;
    top = false;
}

void Player::update(std::vector<SDL_Rect> &tiles, SDL_Rect cameraRect, float dt)
{
    movement(tiles, cameraRect, dt);
}

void Player::draw(SDL_Renderer *renderer, SDL_Rect cameraRect)
{
    SDL_Rect drawingRect = {pPos.x - cameraRect.x, pPos.y - cameraRect.y, 80, 80};
    SDL_RenderCopy(renderer, pTex, &pSrc, &drawingRect);
    // drawingRect = {playerBox.x - cameraRect.x, playerBox.y - cameraRect.y, 40, 56};
    // SDL_RenderDrawRect(renderer, &drawingRect);
}

Player::~Player()
{
    SDL_DestroyTexture(pTex);
}

int Player::getPosX()
{
    return playerBox.x;
}

int Player::getPosY()
{
    return playerBox.y;
}