#include "gameEntity.h"

GameEntity::GameEntity(SDL_Renderer* renderer, double x, double y, int spriteWidth, int spriteHeight)
{
    this->renderer = renderer;
    this->x = x;
    this->y = y;
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;
    dirX = 0;
    dirY = 0;
}
void GameEntity::render()
{
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}