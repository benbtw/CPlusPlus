#pragma once
#include <stdbool.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cmath>

class Player
{
private:
    struct SDL_Texture *pTex;
    struct SDL_Rect pSrc;
    struct SDL_Rect pPos;

    struct SDL_Rect idleLeftAnim[4];
    struct SDL_Rect idleRightAnim[4];
    struct SDL_Rect rightAnim[6];
    struct SDL_Rect leftAnim[6];
    struct SDL_Rect climbAnim[3];
    struct SDL_Rect jumpRightAnim[2];
    struct SDL_Rect jumpLeftAnim[2];

    struct SDL_Point velocity;
    struct SDL_Point gravity;

    int delay;
    int index;
    int maxIndex;
    int speed;
    int sum;

    char direction;

    bool left, right, top, bottom;
    bool grounded;
    float jumpSpeed;

    bool isTouchingTop(SDL_Rect &rect);
    bool isTouchingBottom(SDL_Rect &rect);
    bool isTouchingLeft(SDL_Rect &rect);
    bool isTouchingRight(SDL_Rect &rect);

public:
    void init(SDL_Renderer *renderer);
    ~Player();
    void movement(std::vector<SDL_Rect> &tiles, SDL_Rect cameraRect, float dt);
    void update(std::vector<SDL_Rect> &tiles, SDL_Rect cameraRect, float dt);
    void draw(SDL_Renderer *renderer, SDL_Rect cameraRect);
    int getPosX();
    int getPosY();
    struct SDL_Rect playerBox;
    bool death;
};
