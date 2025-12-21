#ifndef PLAYER_H
#define PLAYER_H
#include "GameEntity.h"

#define PLAYER_SPEED 1

class Player : public GameEntity
{
    public:
        Player(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight);
        void move(double deltaTime) override;
        void handleEvents(SDL_Event& event);
};
#endif