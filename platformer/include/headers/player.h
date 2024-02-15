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
    struct SDL_Rect playerBox;
    struct SDL_Rect colRect;

    struct SDL_Rect idleLeftAnim[4];
    struct SDL_Rect idleRightAnim[4];
    struct SDL_Rect rightAnim[6];
    struct SDL_Rect leftAnim[6];
    struct SDL_Rect climbAnim[3];
    struct SDL_Rect crouchAnim[2];
    struct SDL_Rect jumpAnim[2];
    struct SDL_Rect hurtAnim[2];

    struct SDL_FPoint velocity;

    int delay;
    int index;
    int maxIndex;
    int speed;

    char direction;

    bool left, right, top, bottom;
    bool grounded;
    int gravity;
    float jumpSpeed;

public:
    void init(SDL_Renderer *renderer);
    ~Player();
    void movement(std::vector<SDL_Rect> tiles, SDL_Rect cameraRect);
    void update(std::vector<SDL_Rect> tiles, SDL_Rect cameraRect);
    void draw(SDL_Renderer *renderer, SDL_Rect cameraRect);
    int getPosX();
    int getPosY();
};
