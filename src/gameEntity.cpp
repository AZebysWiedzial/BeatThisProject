#include "gameEntity.h"

GameEntity::GameEntity(SDL_Renderer* renderer, double x, double y, int spriteWidth, int spriteHeight) : Renderable(renderer, x, y, spriteWidth, spriteHeight)
{
    dirX = 0;
    dirY = 0;

    anchor = BOTTOM_CENTER;
}