#include "gameEntity.h"

GameEntity::GameEntity(SDL_Renderer* renderer, SDL_Rect* camera, double x, double y, int spriteWidth, int spriteHeight, int objectWidth, int objectHeight) : Renderable(renderer, camera, x, y, spriteWidth, spriteHeight, objectWidth, objectHeight)
{
    dirX = 0;
    dirY = 0;

    anchor = BOTTOM_CENTER;
}