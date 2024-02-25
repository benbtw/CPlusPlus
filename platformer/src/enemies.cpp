#include "enemies.h"

Enemy::~Enemy()
{
    SDL_DestroyTexture(enemy);
}

void Enemy::init(SDL_Renderer *renderer)
{
    enemy = IMG_LoadTexture(renderer, "res/oposum.png");

    rightAnim[0] = {0, 0, 36, 28};
    rightAnim[1] = {36, 0, 36, 28};
    rightAnim[2] = {72, 0, 36, 28};
    rightAnim[3] = {108, 0, 36, 28};
    rightAnim[4] = {144, 0, 36, 28};
    rightAnim[5] = {180, 0, 36, 28};

    leftAnim[0] = {0, 28, 36, 28};
    leftAnim[1] = {36, 28, 36, 28};
    leftAnim[2] = {72, 28, 36, 28};
    leftAnim[3] = {108, 28, 36, 28};
    leftAnim[4] = {144, 28, 36, 28};
    leftAnim[5] = {180, 28, 36, 28};

    delay = 0;
    index = 0;

    test = {200, 200, 56, 48};

    positions = {
        {1055, 231, 56, 48},
        {1007, 903, 56, 48},
        {2660, 375, 56, 48}};

    direction = 'r';
    speed = 100;
    velocity.x = 0;
    velocity.y = 0;
    maxDist = 0;
    steps = 0;
}

void Enemy::update(float dt, SDL_Rect &playerBox, bool &death)
{
    if (maxDist >= 10)
    {
        velocity.x += speed;
        positions[0].x += velocity.x * dt;
        positions[1].x += velocity.x * dt;
        positions[2].x += velocity.x * dt;
        maxDist = 0;
        steps++;
    }
    if (steps >= 10)
    {
        speed = -speed;
        steps = 0;
        if (direction == 'r')
            direction = 'l';
        else if (direction == 'l')
            direction = 'r';
    }
    maxDist++;
    velocity.x = 0;

    for (SDL_Rect enemy : positions)
    {
        if (SDL_HasIntersection(&playerBox, &enemy))
        {
            death = true;
        }
    }
}

void Enemy::draw(SDL_Renderer *renderer, SDL_Rect cameraRect)
{
    delay++;
    if (delay == 12)
    {
        delay = 0;
        index++;
        if (index >= 6)
            index = 0;
    }
    SDL_Rect drawingRect;
    SDL_Rect colRect;
    for (int i = 0; i < positions.size(); i++)
    {
        drawingRect = {positions[i].x - cameraRect.x, positions[i].y - cameraRect.y, 56, 48};
        if (direction == 'r')
            SDL_RenderCopy(renderer, enemy, &rightAnim[index], &drawingRect);
        else if (direction == 'l')
            SDL_RenderCopy(renderer, enemy, &leftAnim[index], &drawingRect);
    }
}